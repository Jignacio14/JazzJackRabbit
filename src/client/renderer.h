
#ifndef JAZZJACKRABBIT_CONSTANTRATELOOP_H
#define JAZZJACKRABBIT_CONSTANTRATELOOP_H

#include <functional>

class ClientLoop {
private:
  // cppcheck-suppress unusedStructMember
  int client_id;
  // cppcheck-suppress unusedStructMember
  bool keep_running;
  // cppcheck-suppress unusedStructMember
  double rate;

  /*
   * Returns current time in seconds since epoch.
   */
  double now();

public:
  ClientLoop(int id, double rate);

  /*
   * It executes the game logic repeatedly, keeping a constant time rate between
   * each iteration, adjusting the wait time to compensate any possible delay.
   * */
  void run();
};

#endif // JAZZJACKRABBIT_CONSTANTRATELOOP_H
