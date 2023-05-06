#include <SDL2/SDL_events.h>
#include <iostream>
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

bool UIColorButton::clicked() const
{
  if(this->_window->_event->window.windowID == SDL_GetWindowID(this->_window->_window))
  {
    if(this->_window->_mouseX >= this->_position.x && this->_window->_mouseX <= this->_position.x + this->_size.w
       && this->_window->_mouseY >= this->_position.y && this->_window->_mouseY <= this->_position.y + this->_size.h
       && this->_window->_event->type == SDL_MOUSEBUTTONDOWN)
    {
      return true;
    }
  }
  return false;
}
