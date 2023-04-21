#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

#include "ui/ui_window.h"

UIWindow::UIWindow(const std::string &title, UISize size)
{
  /* Do not disable compositor in Xorg */
  putenv((char *)"SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR=0");

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Failed to initialize SDL2, " << SDL_GetError() << std::endl;
    exit(1);
  }

  this->_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.w, size.h, SDL_WINDOW_SHOWN);
  if(!this->_window)
  {
    std::cerr << "Failed to create a window, " << SDL_GetError() << std::endl;
    exit(1);
  }

  this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
  if(!this->_renderer)
  {
    std::cerr << "Failed to create a renderer, " << SDL_GetError() << std::endl;
    exit(1);
  }
}

UIWindow::~UIWindow()
{
  if(this->_renderer)
    SDL_DestroyRenderer(this->_renderer);
  if(this->_window)
    SDL_DestroyWindow(this->_window);
}

void UIWindow::setBackground(UIColor color)
{
  SDL_SetRenderDrawColor(this->_renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(this->_renderer);
}

void UIWindow::draw()
{
  SDL_RenderPresent(this->_renderer);
}

void UIWindow::close()
{
  if(this->_renderer)
  {
    SDL_DestroyRenderer(this->_renderer);
    this->_renderer = nullptr;
  }
  if(this->_window)
  {
    SDL_DestroyWindow(this->_window);
    this->_window = nullptr;
  }
}

void UIWindow::handleEvents(SDL_Event &event)
{
  if(event.window.windowID == SDL_GetWindowID(this->_window))
  {
    SDL_GetMouseState(&this->_mouseX, &this->_mouseY);
    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
      this->close();
  }
}

void UIWindow::setFont(const std::string &font, uint32_t size)
{
  this->_font = UIFont(font, size);
}

SDL_Window *UIWindow::getWindow() const
{
  return this->_window;
}

SDL_Renderer *UIWindow::getRenderer() const
{
  return this->_renderer;
}