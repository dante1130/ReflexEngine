#pragma once

#include "ReflexEngine/ReflexEngine.hpp"
#include "LuaManager.hpp"
#include "NetworkManager.hpp"
#include <time.h>
#include <random>
#include "Controller/ReflexEngine/Camera.hpp"
#include "Controller/Terrain/TexturedTerrain.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"

namespace GenericFunctions {
/**
 * @brief	Exposes generic functions methods to lua
 *
 * @pre		Nothing
 * @post	Exposes funciton to lua
 */
void lua_access();

/**
 * @brief	gets camera x position
 * @return	float	- x position
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamPosX();

/**
 * @brief	gets camera y position
 * @return	float	- y position
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamPosY();

/**
 * @brief	gets camera z position
 * @return	float	- z position
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamPosZ();

/**
 * @brief	gets camera x look
 * @return	float	- x look
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamLookX();

/**
 * @brief	gets camera y look
 * @return	float	- y look
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamLookY();

/**
 * @brief	gets camera z look
 * @return	float	- z look
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamLookZ();

void setPlayableArea(TexturedTerrain* tt, float scale, int size);

float getHeight(float x, float z);

uint8_t* get_height_map();

/**
 * @brief	Creates the network manager
 * @param	create  - if you want to create it
 *
 * @pre		Nothing
 * @post	Creates the network manager
 */
void createNetworkManager(bool create);

/**
 * @brief	Sets the network menu to be active or not
 * @param	active - true if menu should be shown
 *
 * @pre		Nothing
 * @post	Creates/destroys the network menu
 */
void setNetworkMenuActive(bool active);

/**
 * @brief	Gets the active state of the network menu
 * @return	bool - if active
 *
 * @pre		Nothing
 * @post	Gets the active state of the network menu
 */
bool getNetworkMenuActive();

/**
 * @brief	Starts up the network server
 * @param	active - true if starting the network server
 *
 * @pre		CreateNetworkManager called (for initialisation)
 * @post	Server started
 */
void startNetworkServer(bool active);

/**
 * @brief	Connects the client to a server
 *
 * @pre		CreateNetworkManager called (for initialisation)
 * @post	Connects the client to a server using provided IP
 */
void networkClientConnect();

/**
 * @brief	Ends the connection to the network (if client)/Kills the server (if
 * server)
 *
 * @pre		Nothing
 * @post	Gets the active state of the network menu
 */
void networkEnd();

/**
 * @brief	Updates the networkManager (primary used for sending/receiving
 * data). Current use is for connected clients and connection status.
 *
 * @pre		Nothing
 * @post	Updates the network manager so that it can send/receive data packets
 * (primary use is for receiving data packets).
 */
void networkUpdate();

/**
 * @brief	Gets the connection status of the network (if it is connected to
 * either a client or server)
 * @return	bool - true if connected
 *
 * @pre		Nothing
 * @post	returns the connection status of the network
 */
bool networkConnectionStatus();

/**
 * @brief	Retains the IP address entered by the user (catches input that the
 * user has entered with guiManager)
 * @param   savedIP - ip address to retain
 *
 * @pre		Nothing
 * @post	Retains the IP address that has been entered by the user
 */
void networkRetainIP(std::string savedIP);

/**
 * @brief	Retains the message entered by the user (catches input that the
 * user has entered with guiManager)
 * @param   savedMessage - message to retain
 *
 * @pre		Nothing
 * @post	Retains the message that has been entered by the user
 */
void networkRetainMessage(std::string savedMessage);

/**
 * @brief	Returns the message saved by networkRetainMessage
 * @return	string - Returns the retained message
 *
 * @pre		Nothing
 * @post	Returns the retained message
 */
std::string networkReturnRetainedMessage();

/**
 * @brief	Sends the message saved in networkRetainMessage across the network
 *
 * @pre		Nothing
 * @post	Sends the retained message across the network
 */
void networkSendMessage();

/**
 * @brief	Gets a message received across the network
 * @return  string  - The message received by the network manager
 *
 * @pre		Nothing
 * @post	Sends the retained message across the network
 */
std::string networkGetMessage();

/**
 * @brief	Checks if the chat message in networkGetMessage is valid or not
 * @return  bool  - if the chat message is valid or not
 *
 * @pre		Nothing
 * @post	Returns true of the chat message was a valid message
 */
bool networkValidChatMessage();

/**
 * @brief	Checks if the network has connected
 * @return  bool
 *
 * @pre		Nothing
 * @post	Returns if the network has successfully connected
 */
bool networkConnectedSafe();

/**
 * @brief	Checks if the chat message in networkGetMessage is valid or not
 * @return  bool  - if the chat message is valid or not
 *
 * @pre		Nothing
 * @post	Sends the retained message across the network
 */
void networkRetainUsername(std::string savedUsername);

/**
 * @brief	Sets the username of the player
 *
 * @pre		Nothing
 * @post	Sets the username of the player using the retained username
 */
void networkSetUsername();

/**
 * @brief	Returns the username saved in networkRetainUsername
 * @return  string - the username saved by networkRetainUsername
 *
 * @pre		Nothing
 * @post	Returns the username stored by networkRetainUsername
 */
std::string networkReturnUsername();

/**
 * @brief	Sets the pvp network menu to be active or inactive
 * @param	active - true if changing the pvp network menu to be active
 * @return  void
 *
 * @pre		Nothing
 * @post	Sets the pvp network menu to be active or inactive
 */
void setPvPNetworkMenuActive(bool active);

/**
 * @brief	Gets if the pvp network menu is active
 * @return  bool
 *
 * @pre		Nothing
 * @post	Returns true if the pvp network menu is active
 */
bool getPvPNetworkMenuActive();

/**
 * @brief	Gets the network position of the other player
 * @return  float  - get x coordinate position
 *
 * @pre		Nothing
 * @post	Returns the x coordinate of the networked object
 */
float getNetworkPosX();

/**
 * @brief	Gets the network position of the other player
 * @return  float  - get y coordinate position
 *
 * @pre		Nothing
 * @post	Returns the y coordinate of the networked object
 */
float getNetworkPosY();

/**
 * @brief	Gets the network position of the other player
 * @return  float  - get z coordinate position
 *
 * @pre		Nothing
 * @post	Returns the z coordinate of the networked object
 */
float getNetworkPosZ();

/**
 * @brief	Checks if the pvp network manager is receiving data.
 * @return  bool
 *
 * @pre		Nothing
 * @post	Returns true if the network manager is receiving valid data and it
 * is not invalid
 */
bool getReceivingData();

/**
 * @brief	Gets the connection status for the pvp network manager
 * @return  bool
 *
 * @pre		Nothing
 * @post	Returns true if the pvp network manager has successfully connected
 * (automatic success for the server)
 */
bool networkPvPConnectionStatus();

/**
 * @brief	Fixed update loop for the network manager. Primarily used for object
 * replication to improve network performance.
 *
 * @pre		Nothing
 * @post	Update the network on the engine's fixed update loop
 */
void networkFixedUpdate();

/**
 * @brief	Returns the IP address saved by networkRetainIP
 * @return	string - Returns the retained IP address
 *
 * @pre		Nothing
 * @post	Returns the retained IP address
 */
std::string networkReturnRetainedIP();

};  // namespace GenericFunctions
