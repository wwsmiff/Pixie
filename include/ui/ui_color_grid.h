#ifndef UI_COLOR_GRID_H_
#define UI_COLOR_GRID_H_

#include <vector>
#include "ui/ui_color_button.h"
#include "ui/ui_position.h"
#include "ui/ui_size.h"

class UIWindow;

class UIColorGrid
{
public:
  UIColorGrid(UIWindow *window, UIPosition position, UISize size, UISize cellSize, uint32_t padding);
  ~UIColorGrid();

  void import(const std::string &path);
  void update();
  void draw();

  friend UIColorButton;

protected:
  UIWindow *_window;
  UIPosition _position;
  UISize _size, _cellSize;
  uint32_t _padding;
  std::vector<UIColorButton*> _colors;
  uint32_t _selectedColor;
};

#endif /* UI_COLOR_GRID_H_ */