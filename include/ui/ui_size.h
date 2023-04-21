#ifndef UI_SIZE_H_
#define UI_SIZE_H_

#include <cstdint>

struct UISize
{
  uint32_t w, h;

  UISize()
    :w(0), h(0)
  {
  }

  UISize(uint32_t w, uint32_t h)
    :w(w), h(h)
  {
  }

  UISize(uint32_t scalar)
    :w(scalar), h(scalar)
  {
  }

  void set(uint32_t w, uint32_t h)
  {
    this->w = w;
    this->h = h;
  }

  void set(uint32_t scalar)
  {
    this->w = scalar;
    this->h = scalar;
  }
};

#endif /* UI_SIZE_H_ */