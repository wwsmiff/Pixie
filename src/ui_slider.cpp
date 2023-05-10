#include <SDL2/SDL.h>
#include "ui/ui_slider.h"
#include "ui/ui_window.h"

UISlider::UISlider(UIWindow *window, UIPosition position, uint32_t size)
  :_window(window),
   _position(position),
   _size(size)
{
}

UISlider::~UISlider()
{
}

void UISlider::update()
{
}

void UISlider::draw()
{
  SDL_Rect bar = {this->_position.x, this->_position.y, this->_size.w, 7};
  SDL_Rect knob = {this->_position.x, this->_position.y - (7 / 2), 13, 13};

  /* Bar */
  /* background */
  SDL_SetRenderDrawColor(this->_window->_renderer, 200, 200, 200, 255);
  SDL_RenderFillRect(this->_window->_renderer, &bar);
  /* Outline */
  SDL_SetRenderDrawColor(this->_window->_renderer, 0, 0, 0, 255);
  SDL_RenderDrawRect(this->_window->_renderer, &bar);

  /* Knob */
  /* background */
  SDL_SetRenderDrawColor(this->_window->_renderer, 200, 200, 200, 255);
  SDL_RenderFillRect(this->_window->_renderer, &knob);
  /* Outline */
  SDL_SetRenderDrawColor(this->_window->_renderer, 0, 0, 0, 255);
  SDL_RenderDrawRect(this->_window->_renderer, &knob);
}

uint32_t UISlider::getValue() const
{
}
