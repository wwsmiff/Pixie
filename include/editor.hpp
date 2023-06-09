#pragma once

#include <cstdint>
#include <vector>

#include "rgba.hpp"
#include "size.hpp"
#include "window.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace Pixie
{
class Editor
{
public:
  Editor();
  static bool running;

protected:
  void draw();
  void update();
  void mainloop();
  void save();
  void open();
  void addPalette(const std::string &name, const std::string &path,
                  uint32_t width, uint32_t height);
  void drawPalettes();
  static constexpr uint32_t WINDOW_WIDTH = 1600;
  static constexpr uint32_t WINDOW_HEIGHT = 900;
  Pixie::Window mWindow;
  Pixie::Size mCanvasSize;
  Pixie::Size mBlockSize;
  uint32_t mScale{};
  std::vector<Pixie::Rgba> mGrid;
  static Pixie::Rgba mSelectedColor;
};

}; // namespace Pixie
