#include "ui/ui_font.h"
#include <SDL2/SDL.h>
#include <iostream>

UIFont::UIFont() {}

UIFont::UIFont(const std::string &font, uint32_t size)
{
  this->_font = TTF_OpenFont(font.c_str(), size);
  if (!this->_font)
  {
    std::cerr << "Failed to open font: " << font << ", " << TTF_GetError()
              << std::endl;
    exit(1);
  }
  TTF_SetFontHinting(this->_font, TTF_HINTING_LIGHT);
}

UIFont::~UIFont() { this->_cache.clear(); }

void UIFont::draw(const std::string &text, SDL_Renderer *renderer, UIColor fg,
                  UIPosition position, UISize size)
{
  if (this->_cache.find(text) == this->_cache.end())
  {
    SDL_Surface *tmpSurface = TTF_RenderText_Blended(
        this->_font, text.c_str(), SDL_Color{fg.r, fg.g, fg.b, fg.a});
    SDL_Texture *tmpTexture =
        SDL_CreateTextureFromSurface(renderer, tmpSurface);
    this->_cache[text] = tmpTexture;
    SDL_FreeSurface(tmpSurface);
  }

  SDL_Rect upscale = {position.x, position.y, 200, 100};
  SDL_Rect downscale = {position.x, position.y, size.w, size.h};
  SDL_RenderCopy(renderer, this->_cache[text], nullptr, &downscale);
}

void UIFont::draw(const std::string &text, SDL_Renderer *renderer, UIColor fg,
                  SDL_Rect *rect)
{
  if (renderer)
  {
    if (this->_cache.find(text) == this->_cache.end())
    {
      SDL_Surface *tmpSurface = TTF_RenderText_Blended(
          this->_font, text.c_str(), SDL_Color{fg.r, fg.g, fg.b, fg.a});
      SDL_Texture *tmpTexture =
          SDL_CreateTextureFromSurface(renderer, tmpSurface);
      this->_cache[text] = tmpTexture;
      SDL_FreeSurface(tmpSurface);
    }
    SDL_RenderCopy(renderer, this->_cache[text], nullptr, rect);
  }
}
