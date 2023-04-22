#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

#include "editor.h"
#include "ui/ui_window.h"
#include "ui/ui_button.h"
#include "ui/ui_color_palette.h"

bool Editor::running = true;
Editor::Editor()
{
  /* Do not disable compositor in Xorg */
  putenv((char *)"SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR=0");

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Failed to initialize SDL2, " << SDL_GetError() << std::endl;
    exit(1);
  }

  TTF_Init();

  this->_window = SDL_CreateWindow("Sprite Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if(!this->_window)
  {
    std::cerr << "Failed to create a window, " << SDL_GetError() << std::endl;
    exit(1);
  }

  this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_SOFTWARE);
  if(!this->_renderer)
  {
    std::cerr << "Failed to create a renderer, " << SDL_GetError() << std::endl;
    exit(1);
  }
  this->update();
}

Editor::~Editor()
{
  SDL_DestroyRenderer(this->_renderer);
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
}

void cb_fn()
{
  std::cout << "Button 1 clicked" << std::endl;
}

void cb_fn2()
{
  std::cout << "Button 2 clicked" << std::endl;
}

void Editor::update()
{
  SDL_Event event;
  UIWindow testWindow("Test", UISize(600, 800));
  testWindow.setFont("Arial/ARIAL.TTF", 24);

  UIColorPalette palette(&testWindow, UIPosition(10, 10), UISize(8, 2), UISize(30), 0);

  while(this->running)
  {
    if(SDL_PollEvent(&event))
    {
      testWindow.handleEvents(event);
      palette.update(event);
      if(event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(this->_window))
        this->running = false;
    }

    SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->_renderer);
    testWindow.setBackground(UIColor(0x1a1a1aff));

    palette.draw();

    testWindow.draw();
    SDL_RenderPresent(this->_renderer);
  }
}