#ifndef EDITOR_H_
#define EDITOR_H_

#include <cstdint>
#include <vector>

#include "ui/ui_window.h"
#include "ui/ui_color.h"

struct SDL_Window;
struct SDL_Renderer;

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
  UIWindow _window;
  UISize _canvasSize;
  UISize _blockSize;
  uint32_t _scale;
  std::vector<UIColor> _grid;
};

#endif /* EDITOR_H_ */
