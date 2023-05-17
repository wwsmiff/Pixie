#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <span>
#include <string>
#include <vector>

#include "rgba.hpp"
#include "size.hpp"

using std::uint32_t;
using std::uint8_t;

namespace Pixie
{
struct Index2D
{
  uint32_t x{0}, y{0};
};

class Image
{
public:
  Image(uint32_t width, uint32_t height);
  ~Image();
  static void exportToPPM(const Image &input, const std::string &path);
  static void exportToPNG(const Image &input, const std::string &path);
  static void fromRaw(Image &image, const std::vector<Pixie::Rgba> &rawData);
  static Image upscale(const Image &input, uint32_t scale);
  uint32_t width() const;
  uint32_t height() const;
  Pixie::Rgba &operator[](Index2D index);
  const Pixie::Rgba &operator[](Index2D index) const;

private:
  Pixie::Size mExtent;
  std::vector<Pixie::Rgba> mPixels;
};
}; // namespace Pixie
