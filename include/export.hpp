#pragma once

#include <cstdint>
#include <fstream>
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
  Image(const Pixie::Size &size);
  ~Image();
  static void exportToPPM(const Image &input, const std::string &path);
  static void exportToPNG(const Image &input, const std::string &path);
  static void exportToJPG(const Image &input, const std::string &path);
  static void exportToBMP(const Image &input, const std::string &path);
static void loadFromRaw(Image &image,
                          const std::vector<Pixie::Rgba> &rawData);
  static Image upscale(const Image &input, uint32_t scale);
  constexpr uint32_t getWidth() const;
  constexpr uint32_t getHeight() const;
  Pixie::Rgba &operator[](Index2D index);
  const Pixie::Rgba &operator[](Index2D index) const;

private:
  Pixie::Size mExtent;
  std::vector<Pixie::Rgba> mPixels;
};
}; // namespace Pixie
