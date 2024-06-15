#include "./text.h"
#include "./sprite_props.h"

const static char ROBOTO_FONT_PATH[] = "src/client/graphics/Roboto.ttf";
const static char JOYSTIX_FONT_PATH[] = "src/client/ui/assets/Joystix.otf";

Text::Text(GraphicEngine &graphicEngine, std::string &text,
           const SDL2pp::Color &textColor, const int &fontSize,
           const uint8_t &fontCode)
    : sdlRenderer(graphicEngine.getSdlRendererReference()), innerText(text),
      textColor(textColor), fontSize(fontSize), fontCode(fontCode),
      font(this->fontCode == TextFontsCodes::Roboto ? ROBOTO_FONT_PATH
                                                    : JOYSTIX_FONT_PATH,
           this->fontSize),
      textTexture(this->sdlRenderer,
                  this->font.RenderText_Blended(text, this->textColor)) {}

Text::Text(SDL2pp::Renderer &sdlRenderer, std::string &text,
           const SDL2pp::Color &textColor, const int &fontSize,
           const uint8_t &fontCode)
    : sdlRenderer(sdlRenderer), innerText(text), textColor(textColor),
      fontSize(fontSize), fontCode(fontCode),
      font(this->fontCode == TextFontsCodes::Roboto ? ROBOTO_FONT_PATH
                                                    : JOYSTIX_FONT_PATH,
           this->fontSize),
      textTexture(this->sdlRenderer,
                  this->font.RenderText_Blended(text, this->textColor)) {}

Text::Text(SDL2pp::Renderer &sdlRenderer, const char *text,
           const SDL2pp::Color &textColor, const int &fontSize,
           const uint8_t &fontCode)
    : sdlRenderer(sdlRenderer), innerText(text), textColor(textColor),
      fontSize(fontSize), fontCode(fontCode),
      font(this->fontCode == TextFontsCodes::Roboto ? ROBOTO_FONT_PATH
                                                    : JOYSTIX_FONT_PATH,
           this->fontSize),
      textTexture(this->sdlRenderer,
                  this->font.RenderText_Blended(text, this->textColor)) {}

void Text::render(const Coordinates &coords) {

  int width = this->textTexture.GetWidth();
  int height = this->textTexture.GetHeight();

  int positionX = coords.getX();
  int positionY = coords.getY();

  this->sdlRenderer.Copy(this->textTexture, SDL2pp::NullOpt,
                         SDL2pp::Rect(positionX, positionY, width, height));
}

void Text::updateInnerText(const std::string &newText) {
  if (this->innerText == newText) {
    return;
  }

  this->innerText = newText;

  this->textTexture = SDL2pp::Texture(
      this->sdlRenderer,
      this->font.RenderUTF8_Blended(this->innerText, this->textColor));
}
