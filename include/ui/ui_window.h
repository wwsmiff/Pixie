#ifndef UI_WINDOW_H_
#define UI_WINDOW_H_

#include <SDL2/SDL.h>
#include "ui/ui_color.h"
#include "ui/ui_size.h"
#include "ui/ui_font.h"

class UIWindow
{
public:
  UIWindow(const std::string &title, UISize size, SDL_Event *event);
  ~UIWindow();
  void setBackground(UIColor color);
  void draw();
  void close();
  void handleEvents();
  void setFont(const std::string &font, uint32_t size);
  SDL_Window *getWindow() const;
  SDL_Renderer *getRenderer() const;

  friend class Editor;
  friend class UIButton;
  friend class UIColorButton;
  friend class UIColorPalette;
  friend class UISlider;

protected:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  int32_t _mouseX, _mouseY;
  UIFont _font;
  SDL_Event *_event;
};

#endif /* UI_WINDOW_H_ */
