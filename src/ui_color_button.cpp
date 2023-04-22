#include "ui/ui_color_button.h"

UIColorButton::UIColorButton(UIWindow *window, UIColor color, UIColor outline, UIPosition position, UISize size)
  :_window(window),
   _color(color),
   _outline(outline),
   _position(position),
   _size(size)
{
}

UIColorButton::~UIColorButton()
{
}
