#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>
#include <stdio.h>
#include <raknet/Source/RakPeerInterface.h>
#include <raknet/Source/RakNetTypes.h>
#include <raknet/Source/RakString.h>
#include <raknet/Source/BitStream.h>
#include <raknet/Source/MessageIdentifiers.h>

#define MAX_CLIENTS 6
#define SERVER_PORT 60000

//TODO: adjust so can be written for the game asset factory
//      Maybe has it so that all of this (minus GetPacketIdentifier and HandleMessage) can be accessed from Lua?
//      So that anything gui-related written in Lua can easily access the NetworkManager. 
namespace network 
{
	extern char message[512];

	extern char name[256];

	extern char str1[512];

	extern bool isServer;

    
	extern RakNet::RakPeerInterface *peer;

	extern RakNet::Packet *packet;

    ////METHOD NEEDED FOR NETWORK TO OPERATE////
    /**
     * @brief	Initialises Network
     *
     * @param	userName - The username that the client will be using. If this is
     * null, a default name of "Client" will be used. Also sets isServer to
     * "false".
     *
     * @return	Void
     *
     * @pre		None
     * @post	network instance initialised
     */
    void InitNetwork();

    ////METHOD NEEDED FOR NETWORK TO OPERATE FROM THE CLIENT////
    /**
     * @brief	Initialises Network for client. Also handles client username
     *
     * @param	userName - The username that the client will be using. If this is null,
     * a default name of "Client" will be used. Also sets isServer to "false".
     *
     * @return	Void
     *
     * @pre		string username
     * @post	network initialised for client
     */
	void SetupClient(std::string userName);

    /**
     * @brief	Connects the client to the server. Returns true if connection was successful
     * or false if connection was unsuccessful
     * @param	serverIP
     * @return	bool
     *
     * @pre		SetupClient has been run
     * @post	Attempts connection to provided server IP using the port number 60000
     */
	bool ConnectClient(char *serverIP);

    ////METHOD NEEDED FOR NETWORK TO OPERATE FROM THE SERVER////
    /**
     * @brief	Initialises and begins a server session. Running on the network port number 60000. Also sets isServer to "true".
     * @param	void
     * @return	void
     *
     * @pre		None
     * @post	Starts up the server
     */
	void SetupServer();

    /**
     * @brief	Changes the name of the client or server. 
     * @param	userName - the username that the client or server will be using.
     * @return	void
     *
     * @pre		None
     * @post	Changes the user's network name
     */
	void ChangeName(std::string userName);

    /**
     * @brief	Sends a message across the network to the server (or from the server to all connected clients)
     * @param	*inputMessage - The message that will be sent (character limit of 512)
     * @return	void
     *
     * @pre		Either the client has been successfully connected to a server (using ConnectClient),
     * or SetupServer has been run (if the server)
     * @post	Sends a message across the network
     */
	void MessageSend(char *inputMessage);

    /**
     * @brief	Receives a message from the network. This message is sent to the HandleMessage method to determine the message type.
     * @param	void
     * @return	char * - The message
     *
     * @pre		This must be run in a while loop for the network manager to receive messages.
     * @post	Returns the received message to another part of the game engine (notably the gui interface)
     */
	std::string ReceiveMessage();

    /**
     * @brief	Handles the message received and identifies it's message type.
     * @param	Raknet::Packet *packet - the packet of network data.
     * @return	char * - The message of the packet
     *
     * @pre		Called by ReceiveMessage
     * @post	Returns the message based on the packet's ID
     */
	std::string HandleMessage(RakNet::Packet *packet);

    /**
     * @brief	Ends the current session.
     * @param	void
     * @return	void
     *
     * @pre		A session must be running (either ConnectClient or SetupServer must have been run)
     * @post	Ends either the connection to the server or the server itself (depending on the state of the isServer boolean)
     */
	void DestroySession();

    /**
     * @brief	Gets the packet identifier and returns it.
     * @param	Raknet::Packet *packet - the packet of network data.
     * @return	unsigned char - The packet ID
     *
     * @pre		Called by HandleMessage
     * @post	Returns the packet's ID for use in HandleMessage
     */
	unsigned char GetPacketIdentifier(RakNet::Packet *p);

	enum GameMessages{ 
        /// <summary>
	    /// User defined Enumeration for use in message sending
	    /// </summary>
		ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1
	};
 }

#endif