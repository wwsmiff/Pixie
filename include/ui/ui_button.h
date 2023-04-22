#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include <cstdint>
#include <string>
#include "ui/ui_size.h"
#include "ui/ui_position.h"
#include "ui/ui_color.h"

class UIWindow;
// typedef void(*ButtonCallback)();

class UIButton
{
public:
  UIButton(UIWindow *window, const std::string &text, UIPosition position, UISize size, UIColor fg = UIColor(0xFFFFFFFF), UIColor bg = UIColor(0x1a1a1aFF), UIColor outline = UIColor(0xFFFFFFFF));
  ~UIButton();

  // void handleEvents(SDL_Event &event);
  void draw();
  void setFGColor(UIColor color);
  void setBGColor(UIColor color);
  void setOutlineColor(UIColor color);

  bool clicked(SDL_Event &event) const;
 
protected:
  UIWindow *_window;
  UIPosition _position;
  UISize _size;
  UIColor _fg, _bg;
  UIColor _outline;
  std::string _text;
};

#endif /* UI_BUTTON_H_ */