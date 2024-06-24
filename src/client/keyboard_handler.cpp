#include "./keyboard_handler.h"
#include "../data/convention.h"
#include "./stop_iteration_exception.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2pp/SDL2pp.hh>

KeyboardHandler::KeyboardHandler(Client &client, DebugPanel &debugPanel)
    : client(client), debugPanel(debugPanel), allowGameInputs(true) {}

void KeyboardHandler::processAllEvents(const Player &player) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {

    // std::cout << "event: " << event.type << "\n";
    // std::cout << "quit code: " << SDL_QUIT << "\n";

    if (event.key.repeat != 0) {
      continue;
    }

    /*
      SDL_QUIT events
    */

    if (event.type == SDL_QUIT) {
      // std::cout << "QUIT\n";

      throw StopIteration();

      /*
        SDL_KEYDOWN events
      */

    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        throw StopIteration();
        break;

      case SDLK_F1:
        std::cout << "Toggling debug panel"
                  << "\n";
        this->debugPanel.activationToggle();
        break;

      case SDLK_F2:
        this->client.cheat1();
        break;

      case SDLK_F3:
        this->client.cheat2();
        break;

      case SDLK_UP:
        this->client.jump();
        break;

      case SDLK_RIGHT:
        this->client.move_right();
        break;

      case SDLK_LEFT:
        this->client.move_left();
        break;

      case SDLK_SPACE:
        this->client.shoot();
        break;

      case SDLK_LSHIFT:
        this->client.run();
        break;

      case SDLK_q:
        this->client.special_attack();
        break;

      case SDLK_1:
        this->client.change_weapon(GunsIds::Gun1);
        break;

      case SDLK_2:
        this->client.change_weapon(GunsIds::Gun2);
        break;
      }

      /*
        SDL_KEYUP events
      */

    } else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        this->client.stop_moving();
        break;

      case SDLK_RIGHT:
        this->client.stop_moving();
        break;

      case SDLK_LSHIFT:
        this->client.stop_running();
        break;
      }
    }
  }
}

void KeyboardHandler::processOnlyUiEvents(const Player &player) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    // std::cout << "event: " << event.type << "\n";
    // std::cout << "quit code: " << SDL_QUIT << "\n";

    if (event.key.repeat != 0) {
      continue;
    }

    /*
      SDL_QUIT events
    */

    if (event.type == SDL_QUIT) {
      // std::cout << "QUIT\n";
      throw StopIteration();

      /*}else if (event.type == ){
        std::cout << "QUIT EVENT\n"; */

      /*
        SDL_KEYDOWN events
      */

    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        throw StopIteration();
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

void KeyboardHandler::processEvents(const Player &player) {
  if (this->allowGameInputs) {
    this->processAllEvents(player);
  } else {
    this->processOnlyUiEvents(player);
  }
}

void KeyboardHandler::disableGameInputs() { this->allowGameInputs = false; }
