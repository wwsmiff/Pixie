#include "color_palette.hpp"
#include <cstdint>
#include <fstream>
#include <string>

using std::size_t;

namespace Pixie
{
ColorPalette::ColorPalette() {}

ColorPalette::ColorPalette(const std::string &path)
{
  std::ifstream file(path);
  file >> mWidth >> mHeight;
  this->mColors.resize(mWidth * mHeight, 0);
  std::string line{};
  std::getline(file, line);
  for (size_t i{}; std::getline(file, line); ++i)
    this->mColors.at(i) = std::stoul(line, nullptr, 16);
}
}; // namespace Pixie
