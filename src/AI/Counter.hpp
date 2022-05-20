#pragma once

class Counter {
public:
	int increment_count();
	void reset_count();

private:
	int m_count = -1;
};
