
#include "renderer.h"
#include "StopIteration.h"
#include <chrono>
#include <cmath>
#include <thread>

#include "../../common/global_configs.h"
#include "./graphics/jazz.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static double TARGET_FPS = globalConfigs.getTargetFps();
const static double RATE = ((double)1) / TARGET_FPS;

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

const static char *WINDOW_NAME = globalConfigs.getWindowName().c_str();

Renderer::Renderer(int id, Socket socket)
    : client_id(id), keep_running(true), rate(RATE), sdl(SDL_INIT_VIDEO),
      window(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
             SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_SHOWN),
      sdlRenderer(window, -1, SDL_RENDERER_ACCELERATED),
      debugPanel(this->sdlRenderer), client(std::move(socket), id) {}

void Renderer::addRenderable(Renderable *renderable) {
  this->renderables.push_back(renderable);
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
        this->addRenderable(new Jazz(this->sdlRenderer));
        std::cout << "Adding Jazz"
                  << "\n";
        break;

      case SDLK_F1:
        std::cout << "Toggling debug panel"
                  << "\n";
        this->debugPanel.activationToggle();
        break;
      }
    }
  }
}

void Renderer::runMainActions(int iterationNumber) {
  this->processKeyboardEvents();

  this->sdlRenderer.Clear();

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

Renderer::~Renderer() {
  for (auto &renderable : this->renderables) {
    delete renderable;
  }
}
