#ifndef UI_SLIDER_H_
#define UI_SLIDER_H_

#include "ui/ui_size.h"
#include "ui/ui_position.h"

class UIWindow;

class UISlider
{
public:
  UISlider(UIWindow *window, UIPosition position, uint32_t size);
  ~UISlider();

  void update();
  void draw();
  uint32_t getValue() const;

private:
  UIWindow *_window;
  UIPosition _position;
  UISize _size;
  uint32_t _gradient;
};

#endif /* UI_SLIDER_H_ */
