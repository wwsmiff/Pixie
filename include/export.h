#pragma once

#include <array>
#include <vector>
#include <span>
#include <cstdint>
#include <string>
#include <fstream>

#include "ui/ui_color.h"
#include "ui/ui_size.h"

using std::uint8_t;
using std::uint32_t;

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
	static void fromRaw(Image &image, const std::vector<UIColor> &rawData);
	static Image upscale(const Image &input, uint32_t scale);
	uint32_t width() const;
	uint32_t height() const;
	UIColor &operator[](Index2D index);
	const UIColor &operator[](Index2D index) const;

private:	
	UISize _extent;
	std::vector<UIColor> _pixels;
};