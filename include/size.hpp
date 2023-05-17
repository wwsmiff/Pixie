#ifndef UI_SIZE_H_
#define UI_SIZE_H_

#include <cstdint>

namespace Pixie
{

struct Size
{
  uint32_t w, h;

  Size() : w(0), h(0) {}

  Size(uint32_t w, uint32_t h) : w(w), h(h) {}

  Size(uint32_t scalar) : w(scalar), h(scalar) {}

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

}; // namespace Pixie

#endif /* UI_SIZE_H_ */
