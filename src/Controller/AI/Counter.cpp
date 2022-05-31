#include "Counter.hpp"

int Counter::increment_count() {
	m_count++;
	return m_count;
}
void Counter::reset_count() { m_count = -1; }
