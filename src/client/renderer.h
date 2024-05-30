
#ifndef JAZZJACKRABBIT_CONSTANTRATELOOP_H
#define JAZZJACKRABBIT_CONSTANTRATELOOP_H

#include "./debug/debug_panel.h"
#include "./renderable.h"
#include "client.h"
#include <SDL2pp/SDL2pp.hh>
#include <functional>
#include <list>
#include <optional>

class Renderer {
private:
  // cppcheck-suppress unusedStructMember
  int client_id;
  // cppcheck-suppress unusedStructMember
  bool keep_running;
  // cppcheck-suppress unusedStructMember
  double rate;

  SDL2pp::SDL sdl;
  SDL2pp::SDLTTF sdlTtf;
  SDL2pp::Window window;
  SDL2pp::Renderer sdlRenderer;
  // cppcheck-suppress unusedStructMember
  std::list<Renderable *> renderables;
  DebugPanel debugPanel;

  // TEMPORARILY COMMENTED
  // Client client;

  /*
   * Returns current time in seconds since epoch.
   */
  double now();

  void processKeyboardEvents();

  void runMainActions(int iterationNumber);

  void sleep(double timeToSleep);

public:
  Renderer(int id, const char *hostname, const char *port);

  /*
   * It executes the game logic repeatedly, keeping a constant time rate between
   * each iteration, adjusting the wait time to compensate any possible delay.
   * */
  void run();
  void addRenderable(Renderable *renderable);

  ~Renderer();
};

#endif // JAZZJACKRABBIT_CONSTANTRATELOOP_H
