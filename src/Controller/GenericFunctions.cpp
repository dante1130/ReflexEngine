#include "GenericFunctions.h"

static bool m_initRandom = false;
static bool m_useSeed = true;
static int m_seed = 0;

static bool shouldSave = false;
static bool shouldLoad = false;

static int last_save_time_ = -100;
static int last_load_time_ = -100;

static bool helpMenu = false;
static bool networkMenu = false;
static bool networkMenuPvP = false;
static bool credits = false;

static bool createNetwork = false;
static bool networkConnected = false;
static bool createPvPNetwork = false;
static bool pvpNetworkConnected = false;
static bool shouldShoot;
static networkManager network;
static networkManager networkPvP;
static std::string message;
static std::string currentIPAddress;
static std::string incomingMessage;
static std::string username = " ";
static glm::vec3 opponentPos = glm::vec3(50,100,50);
static glm::vec3 prevOpponentPos = glm::vec3(50, 100, 50);
static glm::vec3 previousPos = glm::vec3(0, 0, 0);

static float lastShot = 0;
static float shot_delay = 0;
static uint8_t* m_heightmap;
static TexturedTerrain* m_tt;
static int m_playable_floor_size;
static float m_playable_floor_y_scale;

void GenericFunctions::init_random(int seed, bool useSeed) {
	m_useSeed = useSeed;
	m_seed = seed;

	if (m_useSeed == true) {
		srand(m_seed);
	} else {
		srand(time(nullptr));
	}
	m_initRandom = true;
}

void GenericFunctions::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("window_width", get_window_width);
	lua.set_function("window_height", get_window_height);
	lua.set_function("random_generator", get_random);
	lua.set_function("current_time", get_time);
	lua.set_function("save_game", setIfSave);
	lua.set_function("load_game", setIfLoad);
	lua.set_function("get_load", getIfLoad);
	lua.set_function("time_since_last_save", timeAtLastSave);
	lua.set_function("time_since_last_load", timeAtLastLoad);
	lua.set_function("set_pause_game", setIfPaused);
	lua.set_function("get_pause_game", getIfPaused);
	lua.set_function("exit_game", exitEngine);
	lua.set_function("set_help_menu", setifHelpMenuActive);
	lua.set_function("get_help_menu", getIfHelpMenuActive);
	lua.set_function("set_credits", set_if_credits_active);
	lua.set_function("get_credits", get_if_credits_active);
	lua.set_function("camera_pos_x", luaCamPosX);
	lua.set_function("camera_pos_y", luaCamPosY);
	lua.set_function("camera_pos_z", luaCamPosZ);
	lua.set_function("camera_look_x", luaCamLookX);
	lua.set_function("camera_look_y", luaCamLookY);
	lua.set_function("camera_look_z", luaCamLookZ);

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
	lua.set_function("network_pvp_connection_status", networkPvPConnectionStatus);

	lua.set_function("set_last_shot", setLastShot);
	lua.set_function("set_shot_delay", setShotDelay);
	lua.set_function("set_if_should_shoot", setIfShouldShoot);
	lua.set_function("get_if_should_shoot", getIfShouldShoot);
	lua.set_function("get_y_coord_on_floor", getHeight);
}
//
int GenericFunctions::get_window_width() {
	return ReflexEngine::get_instance().window_.GetBufferWidth();
}

int GenericFunctions::get_window_height() {
	return ReflexEngine::get_instance().window_.GetBufferHeight();
}

int GenericFunctions::get_random(int min, int max) {
	if (m_initRandom == false) {
		init_random(0, true);
	}
	return rand() % max + min;
}

int GenericFunctions::get_time() { return glfwGetTime(); }

bool GenericFunctions::getIfSave() { return shouldSave; }

void GenericFunctions::setIfSave(bool val) {
	shouldSave = val;
	if (val) {
		last_save_time_ = glfwGetTime();
	}
}

int GenericFunctions::timeAtLastSave() { return last_save_time_; }

int GenericFunctions::timeAtLastLoad() { return last_load_time_; }

bool GenericFunctions::getIfLoad() { return shouldLoad; }

void GenericFunctions::setIfLoad(bool val) {
	shouldLoad = val;
	if (val) {
		last_load_time_ = glfwGetTime();
	}
}

bool GenericFunctions::getIfPaused() { return EngineTime::is_paused(); }

void GenericFunctions::setIfPaused(bool val) {
	EngineTime::set_pause(val);

	if (val) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void GenericFunctions::exitEngine() {
	ReflexEngine::get_instance().window_.set_should_close(true);
}

void GenericFunctions::setifHelpMenuActive(bool val) { helpMenu = val; }

bool GenericFunctions::getIfHelpMenuActive() { return helpMenu; }

void GenericFunctions::set_if_credits_active(bool val) { credits = val; }

bool GenericFunctions::get_if_credits_active() { return credits; }

float GenericFunctions::luaCamPosX() {
	return ReflexEngine::get_instance().camera_.get_position().x;
}
float GenericFunctions::luaCamPosY() {
	return ReflexEngine::get_instance().camera_.get_position().y;
}
float GenericFunctions::luaCamPosZ() {
	return ReflexEngine::get_instance().camera_.get_position().z;
}

float GenericFunctions::luaCamLookX() {
	return ReflexEngine::get_instance().camera_.get_direction().x;
}
float GenericFunctions::luaCamLookY() {
	return ReflexEngine::get_instance().camera_.get_direction().y;
}
float GenericFunctions::luaCamLookZ() {
	return ReflexEngine::get_instance().camera_.get_direction().z;
}

void GenericFunctions::setLastShot() { lastShot = glfwGetTime(); }
void GenericFunctions::setShotDelay(float delay) { shot_delay = delay; }
void GenericFunctions::setIfShouldShoot(bool val) {
	if (lastShot < glfwGetTime() - shot_delay) {
		shouldShoot = val;
	} else if (val == false) {
		shouldShoot = val;
	}
}
bool GenericFunctions::getIfShouldShoot() { return shouldShoot; }

void GenericFunctions::setPlayableArea(uint8_t* heightmap, TexturedTerrain* tt,
                                       float scale, int size) {
	// m_heightmap = heightmap;
	m_tt = tt;
	m_playable_floor_size = size;
	m_playable_floor_y_scale = scale;
}

float GenericFunctions::getHeight(float x, float z) {
	return m_tt->get_height_world(x - m_playable_floor_size / 2,
	                              z - m_playable_floor_size / 2) *
	       m_playable_floor_y_scale;
}

uint8_t* GenericFunctions::get_height_map() { return m_tt->get_height_map(); }

void GenericFunctions::createNetworkManager(bool create) {
	if (createNetwork != true && !networkMenuPvP) {
		createNetwork = true;
		network.InitNetwork();
	} else if (createNetwork != true) {
		createPvPNetwork = true;
		networkPvP.InitNetwork();
	}
}

void GenericFunctions::setNetworkMenuActive(bool active) {
	networkMenu = active;
	if (networkMenu) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else if (!networkMenu && !EngineTime::is_paused()) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void GenericFunctions::startNetworkServer(bool active) {
	if (active && !networkMenuPvP) {
		network.SetupServer(username);
		networkConnected = true;
	} else if (active) {
		networkPvP.SetupServer(username);
		pvpNetworkConnected = true;
	}
}

void GenericFunctions::networkClientConnect() {
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

void GenericFunctions::networkEnd() {
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

void GenericFunctions::networkUpdate() {
	
	if (createNetwork && networkConnected){
		incomingMessage = network.ReceiveMessage();
		if (incomingMessage != " ") {
			//printf("%s Update\n", incomingMessage);
		}
	}
	//network.HasReceivedChatMessage();
}

void GenericFunctions::networkFixedUpdate() {
	if (createPvPNetwork && pvpNetworkConnected) {
		if (glm::vec3(luaCamPosX(), luaCamPosY(), luaCamPosZ()) !=
		        previousPos &&
		    networkPvP.ConnectionStatus()) {  // This should reduce how often
			                                  // the position is updated, thus
			                                  // reducing how much data the
			                                  // client and/or server receives
			networkPvP.ObjectPositionSend(
			    glm::vec3(luaCamPosX(), luaCamPosY(), luaCamPosZ()));
			previousPos = glm::vec3(luaCamPosX(), luaCamPosY(), luaCamPosZ());
		}
		prevOpponentPos = opponentPos;
		opponentPos = networkPvP.ObjectPositionReceive();
		if (!getReceivingData()) {
			opponentPos = prevOpponentPos;
		}
	}
}

bool GenericFunctions::getNetworkMenuActive() { return (networkMenu); }

bool GenericFunctions::networkConnectionStatus() {
	bool networkStatus = network.ConnectionStatus();
	return (networkStatus);
}
bool GenericFunctions::networkPvPConnectionStatus() {
	return (networkPvP.ConnectionStatus());
}

void GenericFunctions::networkRetainIP(std::string savedIP) {
	if (savedIP != "") {
		currentIPAddress = savedIP;
	}
}

void GenericFunctions::networkRetainMessage(std::string savedMessage) {
	if (savedMessage != "") {
		message = savedMessage;
	}
}

std::string GenericFunctions::networkReturnRetainedMessage() {
	return (message);
}

void GenericFunctions::networkSendMessage() { 
	char messageChar[512];
	if (network.GetServer()) {
		strcpy(messageChar, message.c_str());
		strcat(messageChar, "\n");
		network.MessageSend(messageChar);
		incomingMessage = network.GetName();
		incomingMessage.append(messageChar);
	}
	networkGetMessage();
}

std::string GenericFunctions::networkGetMessage() {
	return incomingMessage;
}

bool GenericFunctions::networkValidChatMessage(){
	return network.HasReceivedChatMessage();
}

bool GenericFunctions::networkConnectedSafe() {
	return (createNetwork && networkConnected);
}

void GenericFunctions::networkRetainUsername(std::string savedUsername) {
	if (savedUsername != "") {
		username = savedUsername;
	}
}

void GenericFunctions::networkSetUsername() { 
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

std::string GenericFunctions::networkReturnUsername() { 
	return (username); 
}

std::string GenericFunctions::networkReturnRetainedIP() {
	return (currentIPAddress);
}

void GenericFunctions::setPvPNetworkMenuActive(bool active) {
	networkMenuPvP = active;
	if (networkMenuPvP) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else if (!networkMenuPvP && !EngineTime::is_paused()) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

bool GenericFunctions::getPvPNetworkMenuActive() { return networkMenuPvP; }

float GenericFunctions::getNetworkPosX() { return opponentPos.x; }

float GenericFunctions::getNetworkPosY() { return opponentPos.y; }

float GenericFunctions::getNetworkPosZ() { return opponentPos.z; }

bool GenericFunctions::getReceivingData() { 
	//printf("doing get receiving data now\n");
	return !networkPvP.ObjectMissedData();
}
