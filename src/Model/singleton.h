#ifndef __SINGLETON_H
#define __SINGLETON_H

template <class T>
class singleton {
public:
	/**
	 * @brief  Gets the instance of the object
	 * @return	T&	- Object type returned
	 */
	static T& Instance() {
		static T _instance;
		return _instance;
	}

private:
	/**
	 * @brief  Hidden constructor
	 */
	singleton();  // ctor hidden

	/**
	 * @brief  Hidden destructor
	 */
	~singleton();  // dtor hidden

	/**
	 * @brief  Hidden copy constructor
	 */
	singleton(singleton const&);  // copy ctor hidden

	/**
	 * @brief  Hidden assignment opperator
	 */
	singleton& operator=(singleton const&);
};

#endif
