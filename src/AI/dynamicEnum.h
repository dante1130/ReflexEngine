#ifndef __DYNAMICENUM_H
#define __DYNAMICENUM_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class dynamicEnum {
private:
	/// Vector of enums
	vector<string> values;

public:
	/**
	 * @brief	Adds a new enum to the list
	 * @param	description	- The description of the new enum
	 */
	void addValue(string description) { values.push_back(description); }

	/**
	 * @brief	Gets the value of an enum
	 * @param	description	- The description of the new enum
	 * @return	int	- The value of the enum
	 */
	int getValue(string description) {
		if (values.size() == 0) return -1;
		vector<string>::const_iterator iterate;
		int count = 0;
		for (iterate = values.begin(); iterate != values.end(); iterate++) {
			if (description == *iterate) return count;
			count++;
		}
		return -1;
	}

	/**
	 * @brief	Gets the description of an enum
	 * @param	value	- The value of the enum
	 * @return	string	- The description of the enum
	 */
	string getDescription(int value) {
		if (value > values.size() - 1 || value < 0 || values.size() == 0)
			return "INVALID_MESSAGE";
		else {
			return values[value];
		}
	}

	/**
	 * @brief	Outputs the enum
	 * @param	os	- output stream
	 * @param	dn	- The enum to output
	 */
	friend ostream& operator<<(ostream& os, dynamicEnum& dn) {
		string out = "";
		int count = 0;
		vector<string>::iterator iterate;
		for (iterate = dn.values.begin(); iterate != dn.values.end();
		     iterate++) {
			os << count << " " << *iterate << endl;
			count++;
		}

		return os;
	}
};

#endif
