#ifndef UI_COLOR_PALETTE_H_
#define UI_COLOR_PALETTE_H_

#include <vector>
#include "ui/ui_color_button.h"
#include "ui/ui_position.h"
#include "ui/ui_size.h"

class UIWindow;

class UIColorPalette
{
public:
  UIColorPalette(UIWindow *window, UIPosition position, UISize size, UISize cellSize, uint32_t padding);
  ~UIColorPalette();

  void import(const std::string &path);
  void update(SDL_Event &event);
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

#endif /* UI_COLOR_PALETTE_H_ */