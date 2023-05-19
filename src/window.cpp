#include "window.hpp"

SDL_Window *createSDL_Window(const char *title, const Pixie::Size &size)
{
  /* Prevents from disabling the compositor for X11 */
  SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
  SDL_Window *tmp =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       size.w, size.h, SDL_WINDOW_SHOWN);
  if (!tmp)
  {
    std::stringstream errorMessage;
    errorMessage << "Failed to create window, " << SDL_GetError() << std::endl;
    throw std::runtime_error(errorMessage.str());
  }

  return tmp;
}

SDL_Renderer *createSDL_Renderer(SDL_Window *window, int32_t index,
                                 uint32_t flags)
{
  SDL_Renderer *tmp = SDL_CreateRenderer(window, index, flags);

  if (!tmp)
  {
    std::stringstream errorMessage;
    errorMessage << "Failed to create renderer, " << SDL_GetError()
                 << std::endl;
    throw std::runtime_error(errorMessage.str());
  }

  return tmp;
}

namespace Pixie
{
Window::Window(const std::string &title, const Pixie::Size &size)
    : mWindow(createSDL_Window(title.c_str(), size)),
      mRenderer(
          createSDL_Renderer(this->mWindow.get(), -1, SDL_RENDERER_ACCELERATED))
{
}

void Window::handleEvents()
{
  SDL_PollEvent(&this->mEvent);
  if (this->mEvent.window.windowID == SDL_GetWindowID(this->mWindow.get()))
    SDL_GetMouseState(&this->mMouseX, &this->mMouseY);
}

}; // namespace Pixie
