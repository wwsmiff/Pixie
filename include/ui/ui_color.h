#ifndef UI_COLOR_H_
#define UI_COLOR_H_

#include <cstdint>

struct UIColor{
  UIColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
    :r(r), g(g), b(b), a(a)
  {
  }
  UIColor(uint32_t hex)
    :r((hex & 0xFF000000) >> 24),
     g((hex & 0x00FF0000) >> 16),
     b((hex & 0x0000FF00) >> 8),
     a(hex & 0x000000FF)
  {
  }

  void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  void set(uint32_t hex)
  {
    this->r = ((hex & 0xFF000000) >> 24);
    this->g = ((hex & 0x00FF0000) >> 16);
    this->b = ((hex & 0x0000FF00) >> 8);
    this->a = (hex & 0x000000FF);
  }

  ~UIColor()
  {
  }

  void operator+=(uint8_t scalar)
  {
    this->r += scalar;
    this->g += scalar;
    this->b += scalar;
  }

  UIColor operator+(uint8_t scalar)
  {
    return UIColor(this->r + scalar, this->g + scalar, this->b + scalar, this->a); 
  }

  UIColor operator-(uint8_t scalar)
  {
    return UIColor(this->r - scalar, this->g - scalar, this->b - scalar, this->a); 
  }

  uint8_t r, g, b, a;
};

#endif /* UI_COLOR_H_ */