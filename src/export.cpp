#include "export.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace Pixie
{

Image::Image(const Pixie::Size &size)
{
  this->mExtent = size;
  this->mPixels = std::vector<Pixie::Rgba>(size.w * size.h, Pixie::Rgba(0));
}

Image::~Image() {}

void Image::exportToPPM(const Image &input, const std::string &path)
{
  std::ofstream output(path);
  output << "P3\n";
  output << "# " << path << '\n';
  output << input.getWidth() << " " << input.getHeight() << '\n';
  output << "255\n";

  for (uint32_t y = 0; y < input.getHeight(); ++y)
  {
    for (uint32_t x = 0; x < input.getWidth(); ++x)
    {
      Pixie::Rgba current = input.mPixels.at(y * input.getWidth() + x);
      output << static_cast<uint32_t>(current.r) << '\n'
             << static_cast<uint32_t>(current.g) << '\n'
             << static_cast<uint32_t>(current.b) << '\n';
    }
  }

  output.close();
}

void Image::exportToPNG(const Image &input, const std::string &path)
{
  constexpr uint32_t channels = 4;
  stbi_write_png(path.c_str(), input.getWidth(), input.getHeight(), channels,
                 input.mPixels.data(), input.getWidth() * channels);
}

void Image::exportToJPG(const Image &input, const std::string &path)
{
  constexpr uint32_t channels = 4;
  constexpr uint32_t quality = 100;
  stbi_write_jpg(path.c_str(), input.getWidth(), input.getHeight(), channels, input.mPixels.data(), quality);
}

void Image::exportToBMP(const Image &input, const std::string &path)
{
  constexpr uint32_t channels = 4;
  stbi_write_bmp(path.c_str(), input.getWidth(), input.getHeight(), channels, input.mPixels.data());
}

void Image::loadFromRaw(Image &image, const std::vector<Pixie::Rgba> &rawData)
{
  image.mPixels = rawData;
}

constexpr uint32_t Image::getWidth() const { return this->mExtent.w; }

constexpr uint32_t Image::getHeight() const { return this->mExtent.h; }

Pixie::Rgba &Image::operator[](Index2D index)
{
  return this->mPixels.at(index.y * this->mExtent.w + index.x);
}

const Pixie::Rgba &Image::operator[](Index2D index) const
{
  return this->mPixels.at(index.y * this->mExtent.w + index.x);
}

Image Image::upscale(const Image &input, uint32_t scale)
{
  uint32_t target_width_v = input.getWidth() * scale;
  uint32_t target_height_v = input.getHeight() * scale;
  uint32_t x_index{0}, y_index{0};
  Image target_image(Pixie::Size{target_width_v, target_height_v});

  for (y_index = 0; y_index < input.getHeight(); ++y_index)
  {
    for (x_index = 0; x_index < input.getWidth(); ++x_index)
    {
      const Pixie::Rgba &current = input[Index2D{x_index, y_index}];
      if (current.hexRGBA())
      {
        for (uint32_t i = y_index * scale; i < ((y_index + 1) * scale); ++i)
        {
          for (uint32_t j = x_index * scale; j < ((x_index + 1) * scale); ++j)
            target_image[Index2D{j, i}] = current;
        }
      }
    }
  }

  return target_image;
}

}; // namespace Pixie
