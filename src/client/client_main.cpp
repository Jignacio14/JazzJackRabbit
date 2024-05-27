#include "./ui/startup_screen.h"
#include "renderer.h"
#include <cstdint>
#include <iostream>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

const static int EXIT_SUCCESS_CODE = 0;
const static int EXIT_ERROR_CODE = -1;

const static char CHARACTER_NOT_SELECTED = '0';
const static char JAZZ_SELECTED = 'J';
const static char SPAZ_SELECTED = 'S';
const static char LORI_SELECTED = 'L';

std::vector<int> x;
std::vector<int> y;
std::vector<int> w;
std::vector<int> h;
YAML::Node test = YAML::LoadFile("src/client/sprites/test.yaml");
const YAML::Node &frames = test["frames"];
int run_size = frames.size();

void initVectors() {
  for (int i = 0; i < run_size; i++) {
    x.push_back(frames[i]["frame"]["x"].as<int>());
    y.push_back(frames[i]["frame"]["y"].as<int>());
    w.push_back(frames[i]["frame"]["w"].as<int>());
    h.push_back(frames[i]["frame"]["h"].as<int>());
  }
}

void a() {
  // Initialize SDL library
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
  SDL2pp::Window window("JazzJackRabbit 2", SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

  // Create accelerated video renderer with default driver
  SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

  initVectors();
  // Uint32 colorKey = (44 << 16) | (102 << 8) | 150;
  //  Load sprites image as a new texture
  SDL2pp::Surface ss("src/client/sprites/jazz/idle1/composed.png");
  Uint32 colorKey = SDL_MapRGB(ss.Get()->format, 44, 102, 150);
  SDL2pp::Texture sprites(
      renderer, SDL2pp::Surface("src/client/sprites/jazz/idle1/composed.png")
                    .SetColorKey(true, colorKey));

  // Enable alpha blending for the sprites
  sprites.SetBlendMode(SDL_BLENDMODE_BLEND); //.SetColorMod(44, 102, 150);

  // Game state
  int run_phase = -1;   // run animation phase
  float position = 0.0; // player position

  unsigned int prev_ticks = SDL_GetTicks();
  while (true) {
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    // Event processing:
    // - If window is closed, or Q or Escape buttons are pressed,
    //   quit the application
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          return;
        }
      }
    }

    // Update game state for this frame:
    // if character is runnung, move it to the right
    position += frame_delta * 0.2;
    run_phase = (frame_ticks / 100) % run_size;

    // If player passes past the right side of the window, wrap him
    // to the left side
    if (position > renderer.GetOutputWidth())
      position = -50;

    int vcenter =
        renderer.GetOutputHeight() / 2; // Y coordinate of window center

    // Clear screen
    renderer.Clear();

    // Pick sprite from running animantion sequence
    int src_x = x[run_phase];
    int src_y = y[run_phase];

    // Draw player sprite
    renderer.Copy(sprites,
                  SDL2pp::Rect(src_x, src_y, w[run_phase], h[run_phase]),
                  SDL2pp::Rect((int)position, vcenter - h[run_phase],
                               w[run_phase], h[run_phase]));

    // Show rendered frame
    renderer.Present();

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    SDL_Delay(1);
  }
}

int main(int argc, char *argv[]) {
  const uint8_t EXPECTED_ARGUMENTS = 1;

  if (argc != EXPECTED_ARGUMENTS) {
    const std::string errorMessage = "Error while calling program. Expected " +
                                     std::string(argv[0]) +
                                     " call with no extra arguments";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  /*std::string hostname("");
  uint32_t port(0);
  std::string username("");
  char userCharacter = CHARACTER_NOT_SELECTED;
  GameConfigs *game = nullptr;
  GameConfigs **gamePtr = &game;

  StartupScreen startupScreen(argc, argv, hostname, port, username, gamePtr,
                              userCharacter);

  int exitCode = startupScreen.show();

  if (exitCode != EXIT_SUCCESS_CODE) {
    const std::string errorMessage =
        "Error while closing StartupScreen. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  if (game == nullptr) {
    const std::string errorMessage =
        "After closing StartupScreen no game configs detected. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  if (userCharacter == CHARACTER_NOT_SELECTED) {
    const std::string errorMessage =
        "After closing StartupScreen no character selected. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  std::cout << username << "\n";
  std::cout << userCharacter << "\n";
  std::cout << game->getOwnerName() << "|" << game->getCurrentNumberOfPlayers()
            << "/" << game->getMaxNumberOfPlayers() << "\n";
  std::cout << hostname << ":" << port << std::endl;

  int client_id;
  Renderer renderer(client_id, hostname, port);
  renderer.run();

  */

  a();

  return 0; // exitCode;
}
