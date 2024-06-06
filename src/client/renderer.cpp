
#include "renderer.h"
#include "StopIteration.h"
#include <chrono>
#include <cmath>
#include <thread>

#include "../common/global_configs.h"

#include "./graphics/jazz/jazz.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static double TARGET_FPS = globalConfigs.getTargetFps();
const static double RATE = ((double)1) / TARGET_FPS;

Renderer::Renderer(GraphicEngine &graphicEngine, int id, Socket socket)
    : client_id(id), keep_running(true), rate(RATE),
      graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      debugPanel(this->sdlRenderer), client(std::move(socket), id) {}

void Renderer::addRenderable(std::unique_ptr<Renderable> renderable) {
  this->renderables.push_back(std::move(renderable));
}

double Renderer::now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

void Renderer::processKeyboardEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      throw StopIteration();

    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case SDLK_q:
        throw StopIteration();
        break;

      case SDLK_j:
        this->addRenderable(std::make_unique<Jazz>(this->sdlRenderer));
        std::cout << "Adding Jazz"
                  << "\n";
        break;

      case SDLK_F1:
        std::cout << "Toggling debug panel"
                  << "\n";
        this->debugPanel.activationToggle();
        break;

      case SDLK_RIGHT:
        this->client.move_right();
        break;

      case SDLK_LEFT:
        this->client.move_left();
        break;

      case SDLK_SPACE:
        this->client.jump();
        break;
      }
    }
  }
}

void Renderer::runMainActions(int iterationNumber) {

  this->sdlRenderer.Clear();

  std::optional<Snapshot> snapshotOptional = client.get_current_snapshot();
  if (snapshotOptional.has_value()) {
    // cppcheck-suppress unreadVariable
    Snapshot snapshot = snapshotOptional.value();
    //    for (auto &renderable : this->renderables) {
    //      renderable->update(snapshot);
    //    }
  }

  for (auto &renderable : this->renderables) {
    renderable->render(iterationNumber);
  }

  this->debugPanel.display();

  this->processKeyboardEvents();

  this->sdlRenderer.Present();
}

void Renderer::sleep(double timeToSleep) {
  std::this_thread::sleep_for(std::chrono::duration<double>(timeToSleep));
}

void Renderer::run() {
  int iterationNumber = 0;

  while (keep_running) {
    double timestampStart = this->now();

    try {
      this->runMainActions(iterationNumber);
    } catch (const StopIteration &) {
      break;
    }

    double timestampFinish = this->now();
    double timeToRest = rate - (timestampFinish - timestampStart);

    if (timeToRest < 0) {
      double behind = -timeToRest;
      timeToRest = rate - fmod(behind, rate);
      double lost = behind + timeToRest;
      // timestampStart += lost;
      iterationNumber += std::floor(lost / rate);

    } else {
      this->sleep(timeToRest);
      // timestampStart += rate;
      iterationNumber++;
    }

    this->debugPanel.update(this->now());
  }
}

Renderer::~Renderer() {}
