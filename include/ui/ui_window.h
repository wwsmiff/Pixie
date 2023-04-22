#ifndef UI_H_
#define UI_H_

#include <SDL2/SDL.h>
#include "ui/ui_color.h"
#include "ui/ui_size.h"
#include "ui/ui_font.h"

class UIWindow
{
public:
  UIWindow(const std::string &title, UISize size);
  ~UIWindow();
  void setBackground(UIColor color);
  void draw();
  void close();
  void handleEvents(SDL_Event &event);
  void setFont(const std::string &font, uint32_t size);
  SDL_Window *getWindow() const;
  SDL_Renderer *getRenderer() const;

  friend class UIButton;
  friend class UIColorButton;
  friend class UIColorPalette;

protected:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  int32_t _mouseX, _mouseY;
  UIFont _font;
};

#endif /* UI_H_ */