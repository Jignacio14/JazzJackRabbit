
#ifndef JAZZJACKRABBIT_CONSTANTRATELOOP_H
#define JAZZJACKRABBIT_CONSTANTRATELOOP_H

#include "client.h"
#include <functional>

#define RATE 0.04

class Renderer {
private:
  // cppcheck-suppress unusedStructMember
  int client_id;
  // cppcheck-suppress unusedStructMember
  bool keep_running;
  // cppcheck-suppress unusedStructMember
  double rate;

  Client client;

  /*
   * Returns current time in seconds since epoch.
   */
  double now();

public:
  Renderer(int id, Socket &socket);

  /*
   * It executes the game logic repeatedly, keeping a constant time rate between
   * each iteration, adjusting the wait time to compensate any possible delay.
   * */
  void run();
};

#endif // JAZZJACKRABBIT_CONSTANTRATELOOP_H
