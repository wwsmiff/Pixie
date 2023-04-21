#ifndef EDITOR_H_
#define EDITOR_H_

#include <cstdint>
struct SDL_Window;
struct SDL_Renderer;

class Editor
{
public:
  Editor();
  ~Editor();
  void update();
  static bool running;
protected:
  static constexpr uint32_t WINDOW_WIDTH = 1280;
  static constexpr uint32_t WINDOW_HEIGHT = 720;
  SDL_Window *_window = nullptr;
  SDL_Renderer *_renderer = nullptr;
};

#endif /* EDITOR_H_ */