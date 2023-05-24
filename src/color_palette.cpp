#include "color_palette.hpp"
#include <cstdint>
#include <fstream>
#include <string>

using std::size_t;

namespace Pixie
{
ColorPalette::ColorPalette() {}

ColorPalette::ColorPalette(const std::string &path, uint32_t width,
                           uint32_t height)
    : mWidth{width}, mHeight{height}, mColors(width * height, 0)
{
  std::ifstream file(path);
  std::string line{};
  for (size_t i{}; std::getline(file, line); ++i)
    this->mColors.at(i) = std::stoul(line, nullptr, 16);
}
}; // namespace Pixie
