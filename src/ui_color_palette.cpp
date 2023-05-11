#include <SDL2/SDL.h>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "macros.h"
#include "ui/ui_color_button.h"
#include "ui/ui_color_palette.h"
#include "ui/ui_window.h"

uint32_t UIColorPalette::selectedColor = 0;

UIColorPalette::UIColorPalette(UIWindow *window, const std::string &path,
                               UIPosition position, UISize size,
                               UISize cellSize, uint32_t padding)
    : _window(window), _position(position), _size(size), _cellSize(cellSize),
      _padding(padding)
{
  this->import(path);
}

UIColorPalette::~UIColorPalette()
{
  for (size_t i = 0; i < this->_colors.size(); ++i)
    delete this->_colors[i];
}

void UIColorPalette::import(const std::string &path)
{
  std::ifstream inputFile(path);
  std::vector<uint32_t> hexCodes;
  for (std::string line; std::getline(inputFile, line);)
    hexCodes.push_back(std::stoul(line, nullptr, 16));

  ASSERT(((this->_size.w * this->_size.h) == hexCodes.size()),
         "Number of hex values does not match palette size");

  for (uint32_t i = 0; i < this->_size.h; ++i)
  {
    for (uint32_t j = 0; j < this->_size.w; ++j)
    {
      this->_colors.push_back(new UIColorButton(
          this->_window, UIColor(hexCodes[i * this->_size.w + j]),
          UIColor(0x000000FF),
          UIPosition(
              this->_position.x + (j * (this->_cellSize.w + this->_padding)) +
                  this->_cellSize.w,
              this->_position.y + (i * (this->_cellSize.h + this->_padding)) +
                  this->_cellSize.h),
          UISize(this->_cellSize)));
    }
  }
}

void UIColorPalette::draw()
{
  for (size_t i = 0; i < this->_colors.size(); ++i)
  {
    UIColorButton *current = this->_colors[i];
    SDL_Rect tmp = {current->_position.x, current->_position.y,
                    current->_size.w, current->_size.h};
    SDL_SetRenderDrawColor(this->_window->_renderer, current->_color.r,
                           current->_color.g, current->_color.b,
                           current->_color.a);
    SDL_RenderFillRect(this->_window->_renderer, &tmp);
    SDL_SetRenderDrawColor(this->_window->_renderer, current->_outline.r,
                           current->_outline.g, current->_outline.b,
                           current->_outline.a);
    SDL_RenderDrawRect(this->_window->_renderer, &tmp);
  }
}

void UIColorPalette::update()
{
  for (const auto &x : this->_colors)
  {
    if (x->clicked())
      UIColorPalette::selectedColor = x->_color.hex();
  }
}
