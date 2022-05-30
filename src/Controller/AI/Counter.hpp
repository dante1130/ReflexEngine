#pragma once

class Counter {
public:
	/**
	 * @brief	Increments the counter and returns the result
	 * @return	int	- Current counter value
	 */
	int increment_count();

	/**
	 *	@brief	Resets the counter back down to -1 (techically 0 when increment
	 *counter is called)
	 */
	void reset_count();

private:
	/// The count
	int m_count = -1;
};
