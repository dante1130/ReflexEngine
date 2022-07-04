#include "NetworkManager.hpp"

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
		} else {
			connected = true;
		}
		return (connecting);
	}
	return (false);
}

void networkManager::SetupServer(std::string userName) {
	if (peer != NULL && init && !isServer) {
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		peer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
		if (userName != " ") {
			userName.append(": ");
			strcpy(name, userName.c_str());
		} else {
			strcpy(name, "Server: ");
		}
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
		printf("Server Running...\n");
		connected = true;
		connectedClients++;  // Server itself is a client
	}
}

void networkManager::ChangeName(std::string userName) {
	std::string oldName = name;
	std::string updatedName = userName;
	userName.append(": ");
	strcpy(name, userName.c_str());
	if (connected) {
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
		std::string nameChangeMsg;
		char nameChangeChar[256];
		nameChangeMsg.append(oldName);
		nameChangeMsg.append(" Changed their name to ");
		nameChangeMsg.append(updatedName);
		nameChangeMsg.append("\n");
		strcpy(nameChangeChar, nameChangeMsg.c_str());
		printf("%s\n", nameChangeChar);
		bsOut.Write(nameChangeChar);
		peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
		           RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}
}

void networkManager::MessageSend(char* inputMessage) {
	char sendMessage[sizeof(inputMessage) + sizeof(name)];
	strcpy(sendMessage, name);
	strcat(sendMessage, inputMessage);
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
	bsOut.Write(sendMessage);
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
	           RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	// peer->Send(sendMessage, (int)strlen(sendMessage) + 1, HIGH_PRIORITY,
	// RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

std::string networkManager::ReceiveMessage() {
	packet = peer->Receive();
	connected = true;
	if (packet) {
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
					connectedClients++;
					return ("Another client has connected\n");
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
					printf("We have connected\n");
					return ("Our connection request has been accepted\n");
					break;
				case ID_NEW_INCOMING_CONNECTION:
					printf("A Connection is incoming\n");
					connectedClients++;
					return ("A connection is incoming\n");
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					return ("The server is full\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					if (isServer) {
						connected = false;
						connectedClients--;
						return ("A client has disconnected\n");
					} else {
						return ("We have been disconnected\n");
					}
					break;
				case ID_CONNECTION_LOST:
					if (isServer) {
						connected = false;
						connectedClients--;
						RakNet::BitStream bsIn;
						bsIn.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
						bsIn.Write("\nA client has lost connection\n");
						peer->Send(&bsIn, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
						           RakNet::UNASSIGNED_SYSTEM_ADDRESS,
						           true);  // This sends
						                   // the message to everyone
						return ("\nA client lost the connection\n");
					} else {
						return ("Connection lost\n");
					}
					break;
				case ID_GAME_MESSAGE_1: {
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					std::string newMessage = static_cast<std::string>(rs);
					peer->Send(&bsIn, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
					           RakNet::UNASSIGNED_SYSTEM_ADDRESS,
					           true);  // This sends
					                   // the message to everyone
					bsIn.Reset();

					return (newMessage);
					// return (reinterpret_cast<char*>(packet->data));
				}
				default:
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					peer->Send(&bsIn, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
					           RakNet::UNASSIGNED_SYSTEM_ADDRESS,
					           true);  // This sends
					                   // the message to everyone
					return static_cast<std::string>(rs);
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
					connectedClients++;
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
						connectedClients--;
						return ("\nA client has disconnected\n");
					} else {
						connected = false;
						connectedClients--;
						return ("\nWe have been disconnected\n");
					}
					break;
				case ID_CONNECTION_LOST:
					if (isServer) {
						return ("\nA client lost the connection\n");
					} else {
						connected = false;
						connectedClients--;
						return ("Connection lost\n");
					}
					break;
				case ID_GAME_MESSAGE_1: {
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					// printf("%s NM\n", rs.C_String());
					bsIn.Reset();
					return static_cast<std::string>(rs);
					// bsIn.Reset();
				} break;
				default:
					// printf("%s\n", packet->data);
					return " ";
					break;
			}
		}
		peer->DeallocatePacket(packet);
	}
	return " ";
}

void networkManager::DestroySession() {
	if (init) {
		RakNet::RakPeerInterface::DestroyInstance(peer);
		printf("Killed the session\n");
		init = false;
		isServer = false;
		connectedClients = 0;
	}
}

bool networkManager::ConnectionStatus() {
	if (connectedClients > 0) {
		return (true);
	} else {
		return (false);
	}
}

bool networkManager::HasReceivedChatMessage() {
	for (packet = peer->Receive(); packet; packet = peer->Receive()) {
		if (GetPacketIdentifier(packet) == ID_GAME_MESSAGE_1) {
			return (true);
		}
	}
	return (false);
}

char* networkManager::GetName() { return name; }

bool networkManager::GetServer() { return isServer; }

unsigned char networkManager::GetPacketIdentifier(RakNet::Packet* p) {
	if (p == 0) return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP) {
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)
		    p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	} else
		return (unsigned char)p->data[0];
}

void networkManager::ObjectPositionSend(glm::vec3 position) {
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_2);
	bsOut.Write(position);
	//printf("%f %f %f NM\n", position.x, position.y, position.z);
	peer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0,
	           RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

glm::vec3 networkManager::ObjectPositionReceive() {
	packet = peer->Receive();
	if (packet) {
		switch (GetPacketIdentifier(packet)) { 
			case ID_GAME_MESSAGE_2: {
				// RakNet::RakString rs;
				glm::vec3 tempVec3;
				RakNet::BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				bsIn.Read(tempVec3);
				// printf("%f %f %f NM\n", tempVec3.x, tempVec3.y, tempVec3.z);
				bsIn.Reset();
				dataMissed = false;
				return (tempVec3);
				break;
			}
			case ID_CONNECTION_REQUEST_ACCEPTED: {
				connectedClients++;
				break;
			}
			case ID_CONNECTION_LOST: {
				connectedClients--;
				break;
			}
			case ID_DISCONNECTION_NOTIFICATION: {
				connectedClients--;
				break;
			}
		}
	}
	peer->DeallocatePacket(packet);
	//printf("Did not read vector correctly\n");
	dataMissed = true;
	return (glm::vec3(0, 0, 0));
	}