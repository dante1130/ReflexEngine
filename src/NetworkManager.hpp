#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>
#include <raknet/RakPeerInterface.h>
#include <raknet/MessageIdentifiers.h>

#define MAX_CLIENTS 6
#define SERVER_PORT 60000

//TODO: adjust so can be written for the game asset factory
namespace network 
{
	char message[512];

	char name[256];

	char str1[512];

	bool isServer;

	RakNet::RakPeerInterface *peer;

	RakNet::Packet *packet;

	void SetupClient(std::string userName);

	bool ConnectClient(char *serverIP);

	void SetupServer();

	void ChangeName(std::string userName);

	void MessageSend(char *inputMessage);

	char *ReceiveMessage();

	char *HandleMessage(unsigned char packetID);

	void DestroySession();

	unsigned char GetPacketIdentifier(RakNet::Packet *p);

	enum GameMessages{ 
		ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1
	};
 }

#endif