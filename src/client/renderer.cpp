
#include "renderer.h"
#include "StopIteration.h"
#include <chrono>
#include <cmath>
#include <thread>

#include "../common/global_configs.h"

#include "./graphics/jazz/jazz.h"

static const Coordinates DEBUG_INIT_COORDS = Coordinates(0, 0);

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static double TARGET_FPS = globalConfigs.getTargetFps();
const static double RATE = ((double)1) / TARGET_FPS;

Renderer::Renderer(GraphicEngine &graphicEngine, int id, Socket socket,
                   Player &player)
    : client_id(id), keep_running(true), rate(RATE),
      graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      hud(this->graphicEngine), map(this->graphicEngine),
      debugPanel(this->sdlRenderer), client(std::move(socket), id),
      player(player) {}

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

      case SDLK_LEFT:
        this->player.update(true, false, "left");
        break;

      case SDLK_RIGHT:
        this->player.update(true, false, "right");
        break;

      case SDLK_UP:
        this->player.update(true, false, "up");
        break;

      case SDLK_DOWN:
        this->player.update(true, false, "down");
        break;

      case SDLK_j:
        this->addRenderable(
            std::make_unique<Jazz>(this->graphicEngine, DEBUG_INIT_COORDS));
        std::cout << "Adding Jazz"
                  << "\n";
        break;

      case SDLK_F1:
        std::cout << "Toggling debug panel"
                  << "\n";
        this->debugPanel.activationToggle();
        break;
      }
    } else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        this->player.update(false, false, "left");
        break;

      case SDLK_RIGHT:
        this->player.update(false, false, "right");
        break;

      case SDLK_UP:
        this->player.update(false, false, "up");
        break;

      case SDLK_DOWN:
        this->player.update(false, false, "down");
        break;
      }
    }
  }
}

void Renderer::runMainActions(int iterationNumber) {
  this->processKeyboardEvents();

  this->sdlRenderer.Clear();

  this->map.render(iterationNumber);
  this->hud.render(iterationNumber);

  this->player.render(iterationNumber);

  for (auto &renderable : this->renderables) {
    renderable->render(iterationNumber);
  }

  this->debugPanel.display();

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
      iterationNumber += std::floor(lost / rate);

    } else {
      this->sleep(timeToRest);
      iterationNumber++;
    }

    this->debugPanel.update(this->now());
  }
}

Renderer::~Renderer() {}
