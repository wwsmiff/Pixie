#ifndef UI_COLOR_PALETTE_H_
#define UI_COLOR_PALETTE_H_

#include <string>
#include <vector>
#include <cstdint>
#include "ui/ui_position.h"
#include "ui/ui_size.h"

class UIColorButton;
class UIWindow;

class UIColorPalette
{
public:
  UIColorPalette(UIWindow *window, const std::string &path, UIPosition position, UISize size, UISize cellSize, uint32_t padding);
  ~UIColorPalette();

  static uint32_t selectedColor;

  void import(const std::string &path);
  void update();
  void draw();

  friend class UIColorButton;

protected:
  UIWindow *_window;
  UIPosition _position;
  UISize _size, _cellSize;
  uint32_t _padding;
  std::vector<UIColorButton*> _colors;
};

#endif /* UI_COLOR_PALETTE_H_ */
