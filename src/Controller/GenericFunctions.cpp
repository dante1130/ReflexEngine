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
static bool credits = false;

static bool createNetwork = false;
static bool networkConnected = false;
static bool shouldShoot;
static networkManager network;
static std::string message;
static std::string currentIPAddress;

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

	lua.set_function("create_network_manager", createNetworkManager);
	lua.set_function("exit_network_menu", setNetworkMenuActive);
	lua.set_function("get_network_menu", getNetworkMenuActive);
	lua.set_function("start_server", startNetworkServer);
	lua.set_function("network_client_connect", networkClientConnect);
	lua.set_function("network_terminate", networkEnd);
	lua.set_function("network_connection_status", networkConnectionStatus);
	lua.set_function("network_retain_IP", networkRetainIP);
	lua.set_function("network_return_IP", networkReturnRetainedIP);

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
	if (createNetwork != true) {
		createNetwork = true;
		network.InitNetwork();
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
	if (active) {
		network.SetupServer();
		networkConnected = true;
	}
}

void GenericFunctions::networkClientConnect() {
	char serverIPChar[30];
	strcpy(serverIPChar, currentIPAddress.c_str());
	printf("This Runs\n");
	printf("%s\n", currentIPAddress.c_str());
	network.SetupClient("Client");
	networkConnected = !network.ConnectClient(
	    serverIPChar);  // Flipped as it returns true if you are NOT connected
	                    // (which is weird I know)
}

void GenericFunctions::networkEnd() {
	if (createNetwork) {
		network.DestroySession();
		createNetwork = false;
	}
}

void GenericFunctions::networkUpdate() {
	if (createNetwork && networkConnected && network.ReceiveMessage() != " ") {
		printf("%s\n",
		       network.ReceiveMessage());  // Currently prints to console, but
		                                   // will eventually print to text chat
	}
}

bool GenericFunctions::getNetworkMenuActive() { return (networkMenu); }

bool GenericFunctions::networkConnectionStatus() {
	bool networkStatus = network.ConnectionStatus();
	return (networkStatus);
}

void GenericFunctions::networkRetainIP(std::string savedIP) {
	if (savedIP != "") {
		currentIPAddress = savedIP;
	}
}

std::string GenericFunctions::networkReturnRetainedIP() {
	return (currentIPAddress);
}
