#include "ui/ui_button.h"
#include "ui/ui_window.h"
#include <SDL2/SDL.h>
#include <iostream>

UIButton::UIButton(UIWindow *window, const std::string &text,
                   UIPosition position, UISize size, UIColor fg, UIColor bg,
                   UIColor outline)
    : _window(window), _position(position), _size(size), _fg(fg), _bg(bg),
      _outline(outline), _text(text)
{
}

UIButton::~UIButton() {}

void UIButton::draw()
{
  UIColor currentBG = this->_bg;
  UIColor hoverBG = this->_bg + 25;
  UIColor clickedBG = this->_bg - 25;

  if (this->_window->_mouseX >= this->_position.x &&
      this->_window->_mouseX <= this->_position.x + this->_size.w &&
      this->_window->_mouseY >= this->_position.y &&
      this->_window->_mouseY <= this->_position.y + this->_size.h)
    currentBG = hoverBG;
  else
    currentBG = this->_bg;

  SDL_Rect outline = {this->_position.x, this->_position.y, this->_size.w + 1,
                      this->_size.h + 1};
  SDL_Rect background = {this->_position.x, this->_position.y, this->_size.w,
                         this->_size.h};

  /* Background */
  SDL_SetRenderDrawColor(this->_window->_renderer, currentBG.r, currentBG.g,
                         currentBG.b, currentBG.a);
  SDL_RenderFillRect(this->_window->_renderer, &background);
  /* Outline */
  SDL_SetRenderDrawColor(this->_window->_renderer, this->_outline.r,
                         this->_outline.g, this->_outline.b, this->_outline.a);
  SDL_RenderDrawRect(this->_window->_renderer, &outline);

  /* Text */
  this->_window->_font.draw(this->_text, this->_window->_renderer, this->_fg,
                            UIPosition(background.x + 15, background.y + 10),
                            UISize(background.w - 30, background.h - 20));
}

void UIButton::setFGColor(UIColor color) { this->_fg = color; }

void UIButton::setBGColor(UIColor color) { this->_bg = color; }

void UIButton::setOutlineColor(UIColor color) { this->_outline = color; }

bool UIButton::clicked() const
{
  if (this->_window->_event->window.windowID ==
      SDL_GetWindowID(this->_window->_window))
  {
    if (this->_window->_mouseX >= this->_position.x &&
        this->_window->_mouseX <= this->_position.x + this->_size.w &&
        this->_window->_mouseY >= this->_position.y &&
        this->_window->_mouseY <= this->_position.y + this->_size.h &&
        this->_window->_event->type == SDL_MOUSEBUTTONDOWN)
    {
      return true;
    }
  }

  return false;
}
