#include "./text.h"
#include "./sprite_props.h"
#include <iostream>
#include <sstream>

const static char ROBOTO_FONT_PATH[] = "src/client/graphics/Roboto.ttf";
const static char JOYSTIX_FONT_PATH[] = "src/client/ui/assets/Joystix.otf";

Text::Text(GraphicEngine &graphicEngine, std::string &text,
           const SDL2pp::Color &textColor, const int &fontSize,
           const uint8_t &fontCode)
    : sdlRenderer(graphicEngine.getSdlRendererReference()), innerText(text),
      textColor(textColor), fontSize(fontSize), fontCode(fontCode),
      font(this->fontCode == TextFontsCodes::Roboto ? ROBOTO_FONT_PATH
                                                    : JOYSTIX_FONT_PATH,
           this->fontSize) {

  std::basic_stringstream ss(this->innerText);
  std::string line;

  while (std::getline(ss, line, '\n')) {
    SDL2pp::Texture textLineTexture(
        this->sdlRenderer,
        this->font.RenderText_Blended(line, this->textColor));

    this->textTexturesByLine.push_back(std::move(textLineTexture));
  }
}

Text::Text(SDL2pp::Renderer &sdlRenderer, std::string &text,
           const SDL2pp::Color &textColor, const int &fontSize,
           const uint8_t &fontCode)
    : sdlRenderer(sdlRenderer), innerText(text), textColor(textColor),
      fontSize(fontSize), fontCode(fontCode),
      font(this->fontCode == TextFontsCodes::Roboto ? ROBOTO_FONT_PATH
                                                    : JOYSTIX_FONT_PATH,
           this->fontSize) {

  std::basic_stringstream ss(this->innerText);
  std::string line;

  while (std::getline(ss, line, '\n')) {
    SDL2pp::Texture textLineTexture(
        this->sdlRenderer,
        this->font.RenderText_Blended(line, this->textColor));

    this->textTexturesByLine.push_back(std::move(textLineTexture));
  }
}

Text::Text(SDL2pp::Renderer &sdlRenderer, const char *text,
           const SDL2pp::Color &textColor, const int &fontSize,
           const uint8_t &fontCode)
    : sdlRenderer(sdlRenderer), innerText(text), textColor(textColor),
      fontSize(fontSize), fontCode(fontCode),
      font(this->fontCode == TextFontsCodes::Roboto ? ROBOTO_FONT_PATH
                                                    : JOYSTIX_FONT_PATH,
           this->fontSize) {

  std::basic_stringstream ss(this->innerText);
  std::string line;

  while (std::getline(ss, line, '\n')) {
    SDL2pp::Texture textLineTexture(
        this->sdlRenderer,
        this->font.RenderText_Blended(line, this->textColor));

    this->textTexturesByLine.push_back(std::move(textLineTexture));
  }
}

void Text::render(const Coordinates &coords) {
  int positionX = coords.getX();
  int positionY = coords.getY();

  for (auto &textLineTexture : this->textTexturesByLine) {
    int width = textLineTexture.GetWidth();
    int height = textLineTexture.GetHeight();

    this->sdlRenderer.Copy(textLineTexture, SDL2pp::NullOpt,
                           SDL2pp::Rect(positionX, positionY, width, height));
    positionY += height;
  }
}

void Text::updateInnerText(const std::string &newText) {
  if (this->innerText == newText) {
    return;
  }

  this->innerText = newText;

  this->textTexturesByLine.clear();
  std::basic_stringstream ss(this->innerText);
  std::string line;

  while (std::getline(ss, line, '\n')) {
    SDL2pp::Texture textLineTexture(
        this->sdlRenderer,
        this->font.RenderText_Blended(line, this->textColor));

    this->textTexturesByLine.push_back(std::move(textLineTexture));
  }
}
