#ifndef UI_FONT_H_
#define UI_FONT_H_

#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "ui/ui_color.h"
#include "ui/ui_position.h"
#include "ui/ui_size.h"

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

class UIFont
{
public:
  UIFont();
  UIFont(const std::string &font, uint32_t size);
  ~UIFont();
  void draw(const std::string &text, SDL_Renderer *renderer, UIColor fg,
            UIPosition position, UISize size);
  void draw(const std::string &text, SDL_Renderer *renderer, UIColor fg,
            SDL_Rect *rect);

protected:
  TTF_Font *_font = nullptr;
  std::unordered_map<std::string, SDL_Texture *> _cache;
};

#endif /* UI_FONT_H_ */