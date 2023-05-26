#pragma once

#include "rgba.hpp"
#include <cstdint>
#include <string>
#include <vector>

using std::uint32_t;

namespace Pixie
{
class ColorPalette
{
public:
  ColorPalette();
  ColorPalette(const std::string &path);
  constexpr uint32_t getWidth() const { return this->mWidth; }
  constexpr uint32_t getHeight() const { return this->mHeight; }
  const std::vector<Rgba> getColors() const { return this->mColors; }

private:
  uint32_t mWidth{}, mHeight{};
  std::vector<Rgba> mColors;
};

}; // namespace Pixie
