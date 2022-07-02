#include "NetworkAccess.h"

static bool networkMenu = false;
static bool networkMenuPvP = false;

static bool createNetwork = false;
static bool networkConnected = false;
static bool createPvPNetwork = false;
static bool pvpNetworkConnected = false;
static networkManager network;
static networkManager networkPvP;
static std::string message;
static std::string currentIPAddress;
static std::string incomingMessage;
static std::string username = " ";
static glm::vec3 opponentPos = glm::vec3(50, 100, 50);
static glm::vec3 prevOpponentPos = glm::vec3(50, 100, 50);
static glm::vec3 previousPos = glm::vec3(0, 0, 0);

void NetworkAccess::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	// For general network functionality
	lua.set_function("create_network_manager", createNetworkManager);
	lua.set_function("exit_network_menu", setNetworkMenuActive);
	lua.set_function("get_network_menu", getNetworkMenuActive);
	lua.set_function("start_server", startNetworkServer);
	lua.set_function("network_client_connect", networkClientConnect);
	lua.set_function("network_terminate", networkEnd);
	lua.set_function("network_connection_status", networkConnectionStatus);
	lua.set_function("network_retain_IP", networkRetainIP);
	lua.set_function("network_return_IP", networkReturnRetainedIP);

	// For network chat functionality
	lua.set_function("network_retain_message", networkRetainMessage);
	lua.set_function("network_return_message", networkReturnRetainedMessage);
	lua.set_function("network_send_message", networkSendMessage);
	lua.set_function("network_get_message", networkGetMessage);
	lua.set_function("network_has_valid_message", networkValidChatMessage);
	lua.set_function("network_connected", networkConnectedSafe);
	lua.set_function("network_retain_username", networkRetainUsername);
	lua.set_function("network_return_username", networkReturnUsername);
	lua.set_function("network_set_username", networkSetUsername);

	// For network replication functionality
	lua.set_function("exit_pvp_network_menu", setPvPNetworkMenuActive);
	lua.set_function("get_pvp_network_menu", getPvPNetworkMenuActive);
	lua.set_function("get_network_pos_x", getNetworkPosX);
	lua.set_function("get_network_pos_y", getNetworkPosY);
	lua.set_function("get_network_pos_z", getNetworkPosZ);
	lua.set_function("get_receiving_data", getReceivingData);
	lua.set_function("network_pvp_connection_status",
	                 networkPvPConnectionStatus);
}

void NetworkAccess::createNetworkManager(bool create) {
	if (createNetwork != true && !networkMenuPvP) {
		createNetwork = true;
		network.InitNetwork();
	} else if (createPvPNetwork != true) {
		createPvPNetwork = true;
		networkPvP.InitNetwork();
	}
}

void NetworkAccess::setNetworkMenuActive(bool active) {
	networkMenu = active;
	if (networkMenu) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else if (!networkMenu && !EngineTime::is_paused()) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void NetworkAccess::startNetworkServer(bool active) {
	if (active && !networkMenuPvP) {
		network.SetupServer(username);
		networkConnected = true;
	} else if (active) {
		networkPvP.SetupServer(username);
		pvpNetworkConnected = true;
	}
}

void NetworkAccess::networkClientConnect() {
	if (!networkMenuPvP) {
		char serverIPChar[30];
		strcpy(serverIPChar, currentIPAddress.c_str());
		printf("This Runs\n");
		printf("%s\n", currentIPAddress.c_str());
		network.SetupClient(username);
		networkConnected = !network.ConnectClient(
		    serverIPChar);  // Flipped as it returns true if you are NOT
		                    // connected (which is weird I know)
	} else {
		char serverIPChar[30];
		strcpy(serverIPChar, currentIPAddress.c_str());
		printf("This Runs\n");
		printf("%s\n", currentIPAddress.c_str());
		networkPvP.SetupClient(username);
		pvpNetworkConnected = !networkPvP.ConnectClient(
		    serverIPChar);  // Flipped as it returns true if you are NOT
		                    // connected (which is weird I know)
	}
}

void NetworkAccess::networkEnd() {
	if (createNetwork && !networkMenuPvP) {
		network.DestroySession();
		createNetwork = false;
		networkConnected = false;
	} else if (createPvPNetwork) {
		networkPvP.DestroySession();
		pvpNetworkConnected = false;
		createPvPNetwork = false;
	}
}

void NetworkAccess::networkUpdate() {
	if (createNetwork && networkConnected) {
		incomingMessage = network.ReceiveMessage();
		if (incomingMessage != " ") {
			// printf("%s Update\n", incomingMessage);
		}
	}
}

void NetworkAccess::networkFixedUpdate() {
	glm::vec3 camPos = ReflexEngine::get_instance().camera_.get_position();
	if (createPvPNetwork && pvpNetworkConnected) {
		if (glm::vec3(camPos.x, camPos.y, camPos.z) != previousPos &&
		    networkPvP.ConnectionStatus()) {  // This should reduce how often
			                                  // the position is updated, thus
			                                  // reducing how much data the
			                                  // client and/or server receives
			networkPvP.ObjectPositionSend(
			    glm::vec3(camPos.x, camPos.y, camPos.z));
			previousPos = glm::vec3(camPos.x, camPos.y, camPos.z);
		}
		prevOpponentPos = opponentPos;
		opponentPos = networkPvP.ObjectPositionReceive();
		if (!getReceivingData()) {
			opponentPos = prevOpponentPos;
		}
	}
}

bool NetworkAccess::getNetworkMenuActive() { return (networkMenu); }

bool NetworkAccess::networkConnectionStatus() {
	bool networkStatus = network.ConnectionStatus();
	return (networkStatus);
}
bool NetworkAccess::networkPvPConnectionStatus() {
	bool networkPvPStatus = networkPvP.ConnectionStatus();
	return (networkPvPStatus);
}

void NetworkAccess::networkRetainIP(std::string savedIP) {
	if (savedIP != "") {
		currentIPAddress = savedIP;
	}
}

void NetworkAccess::networkRetainMessage(std::string savedMessage) {
	if (savedMessage != "") {
		message = savedMessage;
	}
}

std::string NetworkAccess::networkReturnRetainedMessage() { return (message); }

void NetworkAccess::networkSendMessage() {
	char messageChar[512];
	if (network.GetServer()) {
		strcpy(messageChar, message.c_str());
		strcat(messageChar, "\n");
		network.MessageSend(messageChar);
		incomingMessage = network.GetName();
		incomingMessage.append(messageChar);
	} else {
		strcpy(messageChar, message.c_str());
		strcat(messageChar, "\n");
		network.MessageSend(messageChar);
	}
	networkGetMessage();
}

std::string NetworkAccess::networkGetMessage() { return incomingMessage; }

bool NetworkAccess::networkValidChatMessage() {
	return network.HasReceivedChatMessage();
}

bool NetworkAccess::networkConnectedSafe() {
	return (createNetwork && networkConnected);
}

void NetworkAccess::networkRetainUsername(std::string savedUsername) {
	if (savedUsername != "") {
		username = savedUsername;
	}
}

void NetworkAccess::networkSetUsername() {
	char messageChar[512];
	if (network.GetServer()) {
		strcpy(messageChar, "Changed their name to ");
		strcat(messageChar, username.c_str());
		incomingMessage = network.GetName();
		incomingMessage.append(messageChar);
		incomingMessage.append("\n");
		networkGetMessage();
	}
	network.ChangeName(username);
}

std::string NetworkAccess::networkReturnUsername() { return (username); }

std::string NetworkAccess::networkReturnRetainedIP() {
	return (currentIPAddress);
}

void NetworkAccess::setPvPNetworkMenuActive(bool active) {
	networkMenuPvP = active;
	if (networkMenuPvP) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else if (!networkMenuPvP && !EngineTime::is_paused()) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

bool NetworkAccess::getPvPNetworkMenuActive() { return networkMenuPvP; }

float NetworkAccess::getNetworkPosX() { return opponentPos.x; }

float NetworkAccess::getNetworkPosY() { return opponentPos.y; }

float NetworkAccess::getNetworkPosZ() { return opponentPos.z; }

bool NetworkAccess::getReceivingData() {
	return !networkPvP.ObjectMissedData();
}
