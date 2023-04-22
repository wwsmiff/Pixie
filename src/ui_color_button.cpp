#include <SDL2/SDL_events.h>
#include "ui/ui_window.h"
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

bool UIColorButton::clicked(SDL_Event &event) const
{
  if(event.window.windowID == SDL_GetWindowID(this->_window->_window))
  {
    if(this->_window->_mouseX >= this->_position.x && this->_window->_mouseX <= this->_position.x + this->_size.w
        && this->_window->_mouseY >= this->_position.y && this->_window->_mouseY <= this->_position.y + this->_size.h
        && event.type == SDL_MOUSEBUTTONDOWN)
    {
      return true;
    }
  }
  return false;
}

uint32_t UIColorButton::hex() const
{
  return (this->_color.r << 24 | this->_color.g << 16 | this->_color.b << 8 | this->_color.a);
}