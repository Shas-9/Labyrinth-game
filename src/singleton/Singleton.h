#ifndef SINGLETON_INCLUDE
#define SINGLETON_INCLUDE

class Singleton {
protected:
  Singleton();
public:
  static Singleton& getInstance();
  Singleton(Singleton const&) = delete;
  void operator=(Singleton const&) = delete;
};

#endif