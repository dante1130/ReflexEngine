#include "DynamicDataStorage.hpp"
#include <iostream>

bool DynamicDataStorage::getDynamicBoolData(std::string name, bool init_state) {
	if (bool_map_.find(name) == bool_map_.end()) {
		bool_map_.insert(std::pair<std::string, bool>(name, init_state));
	}
	return bool_map_[name];
}

int DynamicDataStorage::getDynamicIntData(std::string name, int init_state) {
	if (int_map_.find(name) == int_map_.end()) {
		int_map_.insert(std::pair<std::string, int>(name, init_state));
	}
	return int_map_[name];
}

float DynamicDataStorage::getDynamicFloatData(std::string name,
                                              float init_state) {
	if (float_map_.find(name) == float_map_.end()) {
		float_map_.insert(std::pair<std::string, float>(name, init_state));
	}
	return float_map_[name];
}

void DynamicDataStorage::setDynamicBoolData(std::string name, bool value) {
	if (bool_map_.find(name) == bool_map_.end()) {
		bool_map_.insert(std::pair<std::string, bool>(name, value));
	} else {
		bool_map_.at(name) = value;
	}
}

void DynamicDataStorage::setDynamicIntData(std::string name, int value) {
	if (int_map_.find(name) == int_map_.end()) {
		int_map_.insert(std::pair<std::string, int>(name, value));
	} else {
		int_map_.at(name) = value;
	}
}

void DynamicDataStorage::setDynamicFloatData(std::string name, float value) {
	if (float_map_.find(name) == float_map_.end()) {
		float_map_.insert(std::pair<std::string, float>(name, value));
	} else {
		float_map_.at(name) = value;
	}
}
