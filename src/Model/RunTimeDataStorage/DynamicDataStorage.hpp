#pragma once

#include <unordered_map>
#include <iostream>
class DynamicDataStorage {
public:
	bool getDynamicBoolData(std::string name, bool init_state);
	int getDynamicIntData(std::string name, int init_state);
	float getDynamicFloatData(std::string name, float init_state);

	void setDynamicBoolData(std::string name, bool value);
	void setDynamicIntData(std::string name, int value);
	void setDynamicFloatData(std::string name, float value);

private:
	/// An unordered map of boolean values
	std::unordered_map<std::string, int> bool_map_;
	/// An unordered map of int values
	std::unordered_map<std::string, int> int_map_;
	/// An unordered map of float values
	std::unordered_map<std::string, int> float_map_;
};
