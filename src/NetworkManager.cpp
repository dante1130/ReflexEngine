#include "NetworkManager.hpp"

void network::SetupClient(std::string userName) {
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd;
	peer->Startup(1, &sd, 1);
	isServer = false;
	userName.append(": ");
	name = userName;
}

bool network::ConnectClient(char* serverIP) { 
	if (serverIP[0] =='\n') 
	{
		strcpy(serverIP, "127.0.0.1");
	}
	return (peer->Connect(serverIP, SERVER_PORT, 0, 0));
}

void network::SetupServer() {
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(SERVER_PORT, 0);
	peer->Startup(MAX_CLIENTS, &sd, 1);
	isServer = true;
	name = "Server: ";
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);
}

void network::ChangeName(std::string userName) { 
	userName.append(": ");
	name = userName;
}

void network::MessageSend(char* inputMessage) {
	char sendMessage[sizeof(inputMessage) + sizeof(name)];
	strcpy(sendMessage, name);
	strcat(sendMessage, inputMessage);
	peer->Send(sendMessage, (int)strlen(sendMessage) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

char* network::ReceiveMessage() {
	for (packet = peer->Receive(); packet;
		    peer->DeallocatePacket(packet), packet = peer->Receive()) {
		return (HandleMessage(GetPacketIdentifier(packet)));
	}
	
}

char* network::HandleMessage(unsigned char packetID) {
	if (isServer) {
		switch (packetID) {
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				return ("Another client has disconnected\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				return ("Another client has lost the connection\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				return ("Another client has connected\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				return ("Our connection request has been accepted\n");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				return ("A connection is incoming\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				return ("The server is full\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer) {
					return ("A client has disconnected\n");
				} else {
					return ("We have been disconnected\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer) {
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
				return (packet->data);
				// bsIn.Reset();
			} break;
			default:
				peer->Send(message, (const int)strlen(message) + 1,
				           HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				           RakNet::UNASSIGNED_SYSTEM_ADDRESS,
				           true);  // This sends the message to everyone
				break;
		}
	} else {
		switch (packetID) {
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				return ("Another client has disconnected\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				return ("Another client has lost the connection\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				return ("Another client has connected\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				return ("Our connection request has been accepted\n");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				return ("A connection is incoming\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				return ("The server is full\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer) {
					return ("A client has disconnected\n");
				} else {
					return ("We have been disconnected\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer) {
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
				return (packet->data);
				// bsIn.Reset();
			} break;
			default:
				return (packet->data);
				break;
		}
	}
}

void network::DestroySession() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

unsigned char network::GetPacketIdentifier(RakNet::Packet* p) {
	if (p == 0) 
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP) {
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)
		    p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	} else
		return (unsigned char)p->data[0];
}