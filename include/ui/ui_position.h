#ifndef UI_POSITION_y_
#define UI_POSITION_y_

#include <cstdint>

struct UIPosition
{
  uint32_t x, y;

  UIPosition()
    :x(0), y(0)
  {
  }

  UIPosition(uint32_t x, uint32_t y)
    :x(x), y(y)
  {
  }

  UIPosition(uint32_t scalar)
    :x(scalar), y(scalar)
  {
  }

  void set(uint32_t x, uint32_t y)
  {
    this->x = x;
    this->y = y;
  }

  void set(uint32_t scalar)
  {
    this->x = scalar;
    this->y = scalar;
  }
};

#endif /* UI_POSITION_H_ */