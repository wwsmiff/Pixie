#pragma once

#include <cstdint>
#include <vector>

#include "rgba.h"
#include "size.h"
#include "window.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Pixie
{

class Editor
{
public:
  Editor();
  ~Editor();
  void draw();
  void update();
  void save();
  void open();
  void mainloop();

  static bool running;

protected:
  static constexpr uint32_t WINDOW_WIDTH = 1600;
  static constexpr uint32_t WINDOW_HEIGHT = 900;
  Pixie::Window mWindow;
  Pixie::Size mCanvasSize;
  Pixie::Size mBlockSize;
  uint32_t mScale{};
  std::vector<Pixie::Rgba> mGrid;
};

}; // namespace Pixie
