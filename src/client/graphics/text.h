#ifndef JJR_TEXT_H
#define JJR_TEXT_H

#include "../../common/coordinates.h"
#include "./graphic_engine.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/SDL2pp.hh>
#include <string>

class Text {
private:
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  std::string innerText;
  // cppcheck-suppress unusedStructMember
  SDL2pp::Color textColor;
  // cppcheck-suppress unusedStructMember
  int fontSize;
  // cppcheck-suppress unusedStructMember
  uint8_t fontCode;
  // cppcheck-suppress unusedStructMember
  SDL2pp::Font font;
  // cppcheck-suppress unusedStructMember
  SDL2pp::Texture textTexture;

public:
  Text(GraphicEngine &graphicEngine, std::string &text,
       const SDL2pp::Color &textColor, const int &fontSize,
       const uint8_t &fontCode);

  Text(SDL2pp::Renderer &sdlRenderer, std::string &text,
       const SDL2pp::Color &textColor, const int &fontSize,
       const uint8_t &fontCode);

  Text(SDL2pp::Renderer &sdlRenderer, const char *text,
       const SDL2pp::Color &textColor, const int &fontSize,
       const uint8_t &fontCode);

  void render(const Coordinates &coords);
  void updateInnerText(const std::string &newText);
};

#endif // JJR_TEXT_H