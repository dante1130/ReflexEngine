#ifndef __SINGLETON_H
#define __SINGLETON_H

template <class T>
class singleton
{
public:
  static T& Instance() {
    static T _instance;
    return _instance;
  }
private:
  singleton();          // ctor hidden
  ~singleton();          // dtor hidden
  singleton(singleton const&);    // copy ctor hidden
  singleton& operator=(singleton const&);
};

#endif