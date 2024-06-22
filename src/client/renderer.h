
#ifndef JAZZJACKRABBIT_CONSTANTRATELOOP_H
#define JAZZJACKRABBIT_CONSTANTRATELOOP_H

#include "../data/snapshot_dto.h"
#include "./debug/debug_panel.h"
#include "./graphics/graphic_engine.h"
#include "./graphics/hud/hud.h"
#include "./graphics/leaderboard/leaderboard.h"
#include "./graphics/map/map.h"
#include "./keyboard_handler.h"
#include "./player.h"
#include "./renderable.h"
#include "./sound/audio_engine.h"
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
  AudioEngine &audioEngine;
  SDL2pp::Renderer &sdlRenderer;

  // cppcheck-suppress unusedStructMember
  std::list<std::unique_ptr<Renderable>> renderables;
  Player &player;
  Hud hud;
  Map map;
  DebugPanel debugPanel;
  Leaderboard leaderboard;

  Client client;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<SnapshotWrapper> latestSnapshot;

  KeyboardHandler keyboardHandler;

  // cppcheck-suppress unusedStructMember
  uint8_t &scenarioSelected;

  /*
   * Returns current time in seconds since epoch.
   */
  double now();

  void renderGame(int iterationNumber);

  void updateLatestSnapshot();

  void updateGame(int iterationNumber);

  void sleep(double timeToSleep);

  void createNewRenderables();

  void createNewPlayableCharacters(const Snapshot &snapshot);
  void createNewEnemies(const Snapshot &snapshot);
  void createNewCollectables(const Snapshot &snapshot);
  void createNewBullets(const Snapshot &snapshot);

public:
  Renderer(GraphicEngine &graphicEngine, AudioEngine &audioEngine, int id,
           Socket socket, Player &player, SnapshotWrapper &initialSnapshot,
           uint8_t &scenarioSelected);

  /*
   * It executes the game logic repeatedly, keeping a constant time rate between
   * each iteration, adjusting the wait time to compensate any possible delay.
   * */
  void run();
  void addRenderable(std::unique_ptr<Renderable> renderable);

  ~Renderer();
};

#endif // JAZZJACKRABBIT_CONSTANTRATELOOP_H
