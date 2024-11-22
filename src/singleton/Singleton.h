#ifndef SINGLETON_INCLUDE
#define SINGLETON_INCLUDE

template <typename T>
class Singleton {
protected:
  Singleton() {}
public:
  static T& getInstance() {
    static T instance;
    return instance;
  }
  Singleton(Singleton const&) = delete;
  void operator=(Singleton const&) = delete;
};

#endif