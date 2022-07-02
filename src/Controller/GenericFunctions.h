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
 * @brief Get the window width.
 *
 * @return int
 */
int get_window_width();

/**
 * @brief Get the window height.
 *
 * @return int
 */
int get_window_height();

/**
 * @brief	gets if the game should be saved
 * @return	bool	- true if it should be saved
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfSave();

/**
 * @brief	Sets if the game should be saved
 * @param	val	- If the game should be saved
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfSave(bool val);

/**
 * @brief    Resets the time since the last save
 */
void resetSaveSinceLastSave();

/**
 * @brief	Gets time when the game was last saved
 * @return	int	- When the game was last saved
 */
int timeAtLastSave();

/**
 * @brief	Gets time when the game was last loaded
 * @return	int	- When the game was last loaded
 */
int timeAtLastLoad();

/**
 * @brief	Gets time
 * @return	int	- The time
 */
int get_time();

/**
 * @brief	Gets if the game should load game objects from save
 * @return	bool	- If it should load
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfLoad();

/**
 * @brief	Set if game should load objects from save
 * @param	val	- If it should load objects from save
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfLoad(bool val);

/**
 * @brief	Gets if the game should load game objects from scratch
 * @return	bool	- If it should load
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfFullLoad();

/**
 * @brief	Set if game should load objects from scratch
 * @param	val	- If it should load objects from scratch
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfFullLoad(bool val);

/**
 * @brief	Gets if the game should be paused
 * @return	bool	- True if game is paused
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfPaused();

/**
 * @brief	Sets if the game should be paused
 * @param	val	- set true to pause game
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfPaused(bool val);

/**
 * @brief	Exits the game
 *
 * @pre		Nothing
 * @post	Exits engine
 */
void exitEngine();

/**
 * @brief	Sets if the game should show the help menu
 * @param	val	- set true to show help menu
 *
 * @pre		Nothing
 * @post	sets value
 */
void setifHelpMenuActive(bool val);

/**
 * @brief	gets if the game should show the help menu
 * @return	bool	- True if should show help menu
 *
 * @pre		Nothing
 * @post	gets value
 */
bool getIfHelpMenuActive();

/**
 * @brief Set the if credits active.
 *
 * @param val
 */
void set_if_credits_active(bool val);

/**
 * @brief Get the if credits active.
 *
 * @return true
 * @return false
 */
bool get_if_credits_active();

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

/**
 * @brief	Sets when the last shoot was fired (time of this function being
 * called)
 *
 * @pre		Nothing
 * @post	sets last shoot
 */
void setLastShot();

/**
 * @brief	Sets delay between shots
 * @param	delay	- The delay between shots
 *
 * @pre		Nothing
 * @post	sets delay
 */
void setShotDelay(float delay);

/**
 * @brief	Sets if the player should shoot
 * @param	val	- True if the player should shoot
 *
 * @pre		Nothing
 * @post	gets value
 */
void setIfShouldShoot(bool val);

/**
 * @brief	Gets if the player should shoot
 * @return	bool	- true if should shoot
 *
 * @pre		Nothing
 * @post	gets value
 */
bool getIfShouldShoot();

void setPlayableArea(uint8_t* heightmap, TexturedTerrain* tt, float scale,
                     int size);

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
 * @post	Returns true if the network manager is receiving valid data and it is
 * not invalid
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

float getLength(float x, float y);

};  // namespace GenericFunctions
