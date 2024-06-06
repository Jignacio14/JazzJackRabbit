
#ifndef JAZZJACKRABBIT_CONSTANTRATELOOP_H
#define JAZZJACKRABBIT_CONSTANTRATELOOP_H

#include "./debug/debug_panel.h"
#include "./graphics/graphic_engine.h"
#include "./graphics/hud/hud.h"
#include "./graphics/map/map.h"
#include "./renderable.h"
#include "client.h"
#include <SDL2pp/SDL2pp.hh>
#include <functional>
#include <list>
#include <memory>
#include <optional>

class Renderer {
private:
  // cppcheck-suppress unusedStructMember
  int client_id;
  // cppcheck-suppress unusedStructMember
  bool keep_running;
  // cppcheck-suppress unusedStructMember
  double rate;

  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;

  // cppcheck-suppress unusedStructMember
  std::list<std::unique_ptr<Renderable>> renderables;
  Hud hud;
  Map map;
  DebugPanel debugPanel;

  Client client;

  /*
   * Returns current time in seconds since epoch.
   */
  double now();

  void processKeyboardEvents();

  void runMainActions(int iterationNumber);

  void sleep(double timeToSleep);

public:
  Renderer(GraphicEngine &graphicEngine, int id, Socket socket);

  /*
   * It executes the game logic repeatedly, keeping a constant time rate between
   * each iteration, adjusting the wait time to compensate any possible delay.
   * */
  void run();
  void addRenderable(std::unique_ptr<Renderable> renderable);

  ~Renderer();
};

#endif // JAZZJACKRABBIT_CONSTANTRATELOOP_H
