#pragma once

#include <SDL.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "size.hpp"

SDL_Window *createSDL_Window(const char *title, const Pixie::Size &size);

SDL_Renderer *createSDL_Renderer(SDL_Window *window, int32_t index,
                                 uint32_t flags);

namespace Pixie
{
class Window
{
public:
  Window(const std::string &title, const Pixie::Size &size);
  void handleEvents();

protected:
  friend class Editor;

  struct WindowDeleter
  {
    void operator()(SDL_Window *window) const { SDL_DestroyWindow(window); }
  };

  struct RendererDeleter
  {
    void operator()(SDL_Renderer *renderer) const
    {
      SDL_DestroyRenderer(renderer);
    }
  };

  SDL_Event mEvent;
  std::unique_ptr<SDL_Window, WindowDeleter> mWindow{nullptr};
  std::unique_ptr<SDL_Renderer, RendererDeleter> mRenderer{nullptr};

  int32_t mMouseX{}, mMouseY{};
};

}; // namespace Pixie
