#include "NetworkManager.hpp"

char message[512];

char name[256];

bool isServer;

bool connected = false;

bool init = false;

RakNet::RakPeerInterface* peer;

RakNet::Packet* packet;

enum GameMessages {
	ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1
};

void networkManager::InitNetwork() { 
	peer = RakNet::RakPeerInterface::GetInstance();
	init = true;
	printf("Created the network manager.\n");
}

void networkManager::SetupClient(std::string userName) {
	if (peer != NULL && init) {
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &sd, 1);
		isServer = false;
		if (userName != " ") {
			userName.append(": ");
			strcat(name, userName.c_str());
		} else {
			strcat(name, "Client: ");
		}
	}
}

bool networkManager::ConnectClient(char* serverIP) { 
	if (peer != NULL && init) {
		bool connecting;
		if (serverIP[0] == '\n') {
			strcpy(serverIP, "127.0.0.1");
		}
		connecting = peer->Connect(serverIP, SERVER_PORT, 0, 0);
		if (connecting) {
			printf("Not connected");
		}
		return (connecting);
	}
	return (false);
}

void networkManager::SetupServer() {
	if (peer != NULL && init && !isServer) {
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		peer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
		strcat(name, "Server: ");
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
		printf("Server Running...\n");
	}
}

void networkManager::ChangeName(std::string userName) { 
	userName.append(": ");
	strcat(name, userName.c_str());
}

void networkManager::MessageSend(char* inputMessage) {
	char sendMessage[sizeof(inputMessage) + sizeof(name)];
	strcpy(sendMessage, name);
	strcat(sendMessage, inputMessage);
	peer->Send(sendMessage, (int)strlen(sendMessage) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

char* networkManager::ReceiveMessage() {
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
		
		//strcat(message, HandleMessage(packet));
			//return (message);
		connected = true;
		if (isServer) {
			switch (GetPacketIdentifier(packet)) {
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					return ("Another client has disconnected\n");
					break;
				case ID_REMOTE_CONNECTION_LOST:
					return ("Another client has lost the connection\n");
					break;
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					printf("Another Connection is incoming\n");
					return ("Another client has connected\n");
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
					printf("We have connected\n");
					return ("Our connection request has been accepted\n");
					break;
				case ID_NEW_INCOMING_CONNECTION:
					printf("A Connection is incoming\n");
					return ("A connection is incoming\n");
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					return ("The server is full\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					if (isServer) {
						connected = false;
						return ("A client has disconnected\n");
					} else {
						return ("We have been disconnected\n");
					}
					break;
				case ID_CONNECTION_LOST:
					if (isServer) {
						connected = false;
						return ("A client lost the connection\n");
					} else {
						return ("Connection lost\n");
					}
					break;
				case ID_GAME_MESSAGE_1: {
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					return (reinterpret_cast<char*>(packet->data));
				} break;
				default:
					peer->Send(reinterpret_cast<char*>(packet->data), (const int)strlen(reinterpret_cast<char*>(packet->data)) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);  // This sends the message to everyone
					break;
			}
		} else {
			switch (GetPacketIdentifier(packet)) {
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					return ("Another client has disconnected\n");
					break;
				case ID_REMOTE_CONNECTION_LOST:
					return ("Another client has lost the connection\n");
					break;
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					printf("Another Connection is incoming\n");
					return ("Another client has connected\n");
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
					printf("We have connected\n");
					return ("Our connection request has been accepted\n");
					break;
				case ID_NEW_INCOMING_CONNECTION:
					printf("A Connection is incoming\n");
					return ("A connection is incoming\n");
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					return ("The server is full\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					if (isServer) {
						connected = false;
						return ("A client has disconnected\n");
					} else {
						connected = false;
						return ("We have been disconnected\n");
					}
					break;
				case ID_CONNECTION_LOST:
					if (isServer) {
						return ("A client lost the connection\n");
					} else {
						connected = false;
						return ("Connection lost\n");
					}
					break;
				case ID_GAME_MESSAGE_1: {
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					return reinterpret_cast<char*>(packet->data);
					// bsIn.Reset();
				} break;
				default:
					return reinterpret_cast<char*>(packet->data);
					break;
			}
		}
	}
	return (" ");
}

void networkManager::DestroySession() {
	if (init) {
		RakNet::RakPeerInterface::DestroyInstance(peer);
		printf("Killed the session\n");
		init = false;
		isServer = false;
	}
}

bool networkManager::ConnectionStatus() { 
	return (connected);
}

unsigned char networkManager::GetPacketIdentifier(RakNet::Packet* p) {
	if (p == 0) 
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP) {
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)
		    p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	} else
		return (unsigned char)p->data[0];
}