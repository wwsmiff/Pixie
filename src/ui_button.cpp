#include <SDL2/SDL.h>
#include <iostream>
#include "ui/ui_button.h"
#include "ui/ui_window.h"

UIButton::UIButton(UIWindow *window, const std::string &text, UIPosition position, UISize size, UIColor fg, UIColor bg, UIColor outline)
  :_window(window),
   _position(position),
   _size(size),
   _fg(fg),
   _bg(bg),
   _outline(outline),
   _text(text)
{
}

UIButton::~UIButton()
{
}

void UIButton::draw()
{
  SDL_Rect outline = {this->_position.x, this->_position.y, this->_size.w + 1, this->_size.h + 1};
  SDL_Rect background = {this->_position.x, this->_position.y, this->_size.w, this->_size.h};

  /* Background */
  SDL_SetRenderDrawColor(this->_window->_renderer, this->_bg.r, this->_bg.g, this->_bg.b, this->_bg.a);
  SDL_RenderFillRect(this->_window->_renderer, &background);  
  /* Outline */
  SDL_SetRenderDrawColor(this->_window->_renderer, this->_outline.r, this->_outline.g, this->_outline.b, this->_outline.a);
  SDL_RenderDrawRect(this->_window->_renderer, &outline);

  /* Text */
  this->_window->_font.draw(this->_text, this->_window->_renderer, this->_fg, UIPosition(background.x + 12, background.y + 6), UISize(background.w - 24, background.h - 12));
}

// void UIButton::handleEvents(SDL_Event &event)
// {

//   if(event.window.windowID == SDL_GetWindowID(this->_window->_window))
//   {
//     if(this->_window->_mouseX >= this->_position.x && this->_window->_mouseX <= this->_position.x + this->_size.w
//        && this->_window->_mouseY >= this->_position.y && this->_window->_mouseY <= this->_position.y + this->_size.h
//        && event.type == SDL_MOUSEBUTTONDOWN)
//     {
//     }
//   }
// }

void UIButton::setFGColor(UIColor color)
{
  this->_fg = color;
}

void UIButton::setBGColor(UIColor color)
{
  this->_bg = color;
}

void UIButton::setOutlineColor(UIColor color)
{
  this->_outline = color;
}

bool UIButton::clicked(SDL_Event &event) const
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
}