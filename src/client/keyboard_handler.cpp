#include "./keyboard_handler.h"
#include "../data/convention.h"
#include "./stop_iteration_exception.h"
#include <SDL2pp/SDL2pp.hh>

KeyboardHandler::KeyboardHandler(Client &client, DebugPanel &debugPanel)
    : client(client), debugPanel(debugPanel) {}

void KeyboardHandler::processEvents(const Player &player) {
  const PlayerDto &playerInfo = player.getPlayerDtoReference();
  SDL_Event event;
  while (SDL_PollEvent(&event)) {

    if (event.key.repeat != 0) {
      continue;
    }
    if (event.type == SDL_QUIT) {
      throw StopIteration();

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

      case SDLK_UP:
        /*if (playerInfo.is_jumping || playerInfo.is_falling) {
          break;
        }*/
        this->client.jump();
        break;

      case SDLK_RIGHT:
        /*if (playerInfo.is_walking || playerInfo.is_running) {
          break;
        }*/
        this->client.move_right();
        break;

      case SDLK_LEFT:
        /*if (playerInfo.is_walking || playerInfo.is_running) {
          break;
        }*/
        this->client.move_left();
        break;

      case SDLK_SPACE:
        this->client.shoot();
        break;

      case SDLK_LSHIFT:
        if (playerInfo.is_running) {
          break;
        }
        this->client.run();
        break;

      case SDLK_LCTRL:
        this->client.special_attack();
        break;

      case SDLK_1:
        this->client.change_weapon(GunsIds::Gun1);
        break;

      case SDLK_2:
        this->client.change_weapon(GunsIds::Gun2);
        break;
      }
    } else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        /*if (playerInfo.is_walking || playerInfo.is_running) {
          this->client.stop_moving();
        }*/
        break;

      case SDLK_RIGHT:
        this->client.stop_moving();
        break;
      case SDLK_LEFT:
        this->client.stop_moving();
        break;
      case SDLK_LSHIFT:
        this->client.stop_running();
        break;
      }
    }
  }
}
