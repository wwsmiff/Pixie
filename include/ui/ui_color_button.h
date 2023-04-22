#ifndef UI_COLOR_BUTTON_H_
#define UI_COLOR_BUTTON_H_

#include <cstdint>
#include "ui/ui_color.h"
#include "ui/ui_position.h"
#include "ui/ui_size.h"

typedef void(*ColorButtonCallback)(uint32_t);

union SDL_Event;
class UIWindow;

class UIColorButton
{
public:
  UIColorButton(UIWindow *window, UIColor color, UIColor outline, UIPosition position, UISize size);
  ~UIColorButton();

  void update();
  void draw();
  uint32_t hex() const;

  bool clicked(SDL_Event &event) const;

  friend class UIColorPalette;

protected:
  UIColor _color;
  UIColor _outline;
  UIPosition _position;
  UISize _size;
  UIWindow *_window;
};

#endif /* UI_COLOR_BUTTON_H_ */