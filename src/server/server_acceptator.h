#ifndef SERVER_ACCEPTATOR
#define SERVER_ACCEPTATOR

#include "../common/thread.h"
#include <string>

class Acceptator : public Thread {
private:
public:
  explicit Acceptator(const std::string &port);
  void run() override;
  void kill();
  ~Acceptator();
};
#endif
