
#include "./renderer.h"
#include "../common/jjr2_error.h"
#include "../common/snapshot_wrapper.h"
#include "./stop_iteration_exception.h"
#include <chrono>
#include <cmath>
#include <thread>

#include "../common/global_configs.h"

#include "./graphics/bullets/bullet_gun_1.h"
#include "./graphics/bullets/bullet_gun_2.h"
#include "./graphics/collectables/ammo_gun_1.h"
#include "./graphics/collectables/ammo_gun_2.h"
#include "./graphics/collectables/carrot.h"
#include "./graphics/collectables/coin.h"
#include "./graphics/collectables/diamond.h"
#include "./graphics/enemies/bubba.h"
#include "./graphics/enemies/schwarzenguard.h"
#include "./graphics/enemies/turtle_goon.h"
#include "./graphics/jazz/jazz.h"
#include "./graphics/lori/lori.h"
#include "./graphics/spaz/spaz.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static double TARGET_FPS = globalConfigs.getTargetFps();
const static double RATE = ((double)1) / TARGET_FPS;

Renderer::Renderer(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
                   int id, Socket socket, Player &player,
                   SnapshotWrapper &initialSnapshot)
    : client_id(id), keep_running(true), rate(RATE),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      player(player), hud(this->graphicEngine, this->player),
      map(this->graphicEngine, this->player), debugPanel(this->sdlRenderer),
      leaderboard(this->sdlRenderer,
                  this->graphicEngine.getLeaderboardSprite()),
      client(std::move(socket), id),
      latestSnapshot(std::make_unique<SnapshotWrapper>(
          initialSnapshot.transferSnapshotDto())),
      keyboardHandler(this->client, this->debugPanel) {}

void Renderer::addRenderable(std::unique_ptr<Renderable> renderable) {
  this->renderables.push_back(std::move(renderable));
}

double Renderer::now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

void Renderer::renderGame(int iterationNumber) {
  this->sdlRenderer.Clear();

  this->map.render(iterationNumber);
  this->map.renderPlayer(iterationNumber);

  const Coordinates &leftCorner = this->map.getLeftCorner();
  for (auto &renderable : this->renderables) {
    renderable->renderFromLeftCorner(iterationNumber, leftCorner);
  }

  this->hud.render(*this->latestSnapshot);

  if (this->latestSnapshot->didGameEnd()) {
    this->leaderboard.display(*this->latestSnapshot);
  }

  this->debugPanel.display();
  this->sdlRenderer.Present();
}

void Renderer::updateLatestSnapshot() {
  std::unique_ptr<Snapshot> snapshotDto = this->client.get_current_snapshot();

  while (snapshotDto != nullptr) {
    this->latestSnapshot =
        std::make_unique<SnapshotWrapper>(std::move(snapshotDto));

    this->player.update(*this->latestSnapshot);

    for (auto &renderable : this->renderables) {
      renderable->update(*this->latestSnapshot);
    }

    this->createNewRenderables();

    snapshotDto = this->client.get_current_snapshot();
  }
}

void Renderer::updateGame(int iterationNumber) {
  if (this->latestSnapshot->didGameEnd()) {
    return;
  }

  renderables.remove_if([](const std::unique_ptr<Renderable> &renderable) {
    return renderable->shouldDelete();
  });

  this->updateLatestSnapshot();
}

void Renderer::createNewPlayableCharacters(const Snapshot &snapshot) {
  for (int i = 0; i < snapshot.sizePlayers; i++) {
    bool exists =
        std::any_of(this->renderables.begin(), this->renderables.end(),
                    [snapshot, i](const auto &renderable) {
                      return snapshot.players[i].user_id == renderable->getId();
                    });

    if (exists) {
      continue;
    }

    Coordinates coords(snapshot.players[i].position_x,
                       snapshot.players[i].position_y);
    SnapshotWrapper &storedSnapshotWrapper = std::ref(*this->latestSnapshot);

    switch (snapshot.players[i].type) {
    case PlayableCharactersIds::Jazz:
      this->addRenderable(std::make_unique<Jazz>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.players[i].user_id, storedSnapshotWrapper));
      break;
    case PlayableCharactersIds::Spaz:
      this->addRenderable(std::make_unique<Spaz>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.players[i].user_id, storedSnapshotWrapper));
      break;
    case PlayableCharactersIds::Lori:
      this->addRenderable(std::make_unique<Lori>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.players[i].user_id, storedSnapshotWrapper));
      break;
    }
  }
}

void Renderer::createNewEnemies(const Snapshot &snapshot) {
  for (int i = 0; i < snapshot.sizeEnemies; i++) {
    bool exists = std::any_of(
        this->renderables.begin(), this->renderables.end(),
        [snapshot, i](const auto &renderable) {
          return snapshot.enemies[i].entity_id == renderable->getId();
        });

    if (exists) {
      continue;
    }

    Coordinates coords(snapshot.enemies[i].position_x,
                       snapshot.enemies[i].position_y);
    SnapshotWrapper &storedSnapshotWrapper = std::ref(*this->latestSnapshot);

    switch (snapshot.enemies[i].type) {
    case EnemiesIds::Bubba:
      this->addRenderable(std::make_unique<Bubba>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.enemies[i].entity_id, storedSnapshotWrapper));
      break;
    case EnemiesIds::TurtleGoon:
      this->addRenderable(std::make_unique<TurtleGoon>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.enemies[i].entity_id, storedSnapshotWrapper));
      break;
    case EnemiesIds::Schwarzenguard:
      this->addRenderable(std::make_unique<Schwarzenguard>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.enemies[i].entity_id, storedSnapshotWrapper));
      break;
    }
  }
}

void Renderer::createNewCollectables(const Snapshot &snapshot) {
  for (int i = 0; i < snapshot.sizeCollectables; i++) {
    bool exists = std::any_of(
        this->renderables.begin(), this->renderables.end(),
        [snapshot, i](const auto &renderable) {
          return snapshot.collectables[i].entity_id == renderable->getId();
        });

    if (exists) {
      continue;
    }

    Coordinates coords(snapshot.collectables[i].position_x,
                       snapshot.collectables[i].position_y);
    SnapshotWrapper &storedSnapshotWrapper = std::ref(*this->latestSnapshot);

    switch (snapshot.collectables[i].type) {
    case CollectableIds::Coin:
      this->addRenderable(std::make_unique<Coin>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.collectables[i].entity_id, storedSnapshotWrapper));
      break;
    case CollectableIds::Diamond:
      this->addRenderable(std::make_unique<Diamond>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.collectables[i].entity_id, storedSnapshotWrapper));
      break;
    case CollectableIds::Carrot:
      this->addRenderable(std::make_unique<Carrot>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.collectables[i].entity_id, storedSnapshotWrapper));
      break;
    case CollectableIds::AmmoGun1:
      this->addRenderable(std::make_unique<AmmoGun1>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.collectables[i].entity_id, storedSnapshotWrapper));
      break;
    case CollectableIds::AmmoGun2:
      this->addRenderable(std::make_unique<AmmoGun2>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.collectables[i].entity_id, storedSnapshotWrapper));
      break;
    }
  }
}

void Renderer::createNewBullets(const Snapshot &snapshot) {
  for (int i = 0; i < snapshot.sizeBullets; i++) {
    bool exists = std::any_of(
        this->renderables.begin(), this->renderables.end(),
        [snapshot, i](const auto &renderable) {
          return snapshot.bullets[i].entity_id == renderable->getId();
        });

    if (exists) {
      continue;
    }

    Coordinates coords(snapshot.bullets[i].position_x,
                       snapshot.bullets[i].position_y);
    SnapshotWrapper &storedSnapshotWrapper = std::ref(*this->latestSnapshot);

    switch (snapshot.bullets[i].type) {
    case GunsIds::Gun1:
      this->addRenderable(std::make_unique<BulletGun1>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.bullets[i].entity_id, storedSnapshotWrapper));
      break;
    case GunsIds::Gun2:
      this->addRenderable(std::make_unique<BulletGun1>(
          this->graphicEngine, this->audioEngine, coords,
          snapshot.bullets[i].entity_id, storedSnapshotWrapper));
      break;
    }
  }
}

void Renderer::createNewRenderables() {
  const Snapshot &snapshot = this->latestSnapshot->getSnapshotReference();
  this->createNewPlayableCharacters(snapshot);
  this->createNewEnemies(snapshot);
  this->createNewCollectables(snapshot);
  this->createNewBullets(snapshot);
}

void Renderer::sleep(double timeToSleep) {
  std::this_thread::sleep_for(std::chrono::duration<double>(timeToSleep));
}

void Renderer::run() {
  int iterationNumber = 0;

  while (keep_running) {
    double timestampStart = this->now();

    try {
      this->renderGame(iterationNumber);
      this->updateGame(iterationNumber);
      this->keyboardHandler.processEvents(this->player);
    } catch (const StopIteration &) {
      break;
    }

    if (!this->client.isAlive() && !this->latestSnapshot->didGameEnd()) {
      std::string errorMessage =
          "Client stopped due to connection with server broken";
      throw JJR2Error(errorMessage, __LINE__, __FILE__);
    }

    double timestampFinish = this->now();
    double timeToRest = rate - (timestampFinish - timestampStart);

    if (timeToRest < 0) {
      double behind = -timeToRest;
      timeToRest = rate - fmod(behind, rate);
      double lost = behind + timeToRest;
      iterationNumber += std::floor(lost / rate);

    } else {
      this->sleep(timeToRest);
      iterationNumber++;
    }

    this->debugPanel.update(this->now());
  }
}

Renderer::~Renderer() {}