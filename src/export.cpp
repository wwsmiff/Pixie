#include <cstdlib>
#include <iostream>
#include "export.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_writer.h"

Image::Image(uint32_t width, uint32_t height)
{
	this->_extent = UISize(width, height);
	this->_pixels = std::vector<UIColor>(width * height,UIColor(0));
}

Image::~Image()
{
}

void Image::exportToPPM(const Image &input, const std::string &path)
{
	std::ofstream output(path);
	output << "P3\n";
	output << "# " << path << '\n';
	output << input.width() << " " << input.height() << '\n';
	output << "255\n"; 
	
	for(uint32_t y = 0; y < input.height(); ++y)
	{
		for(uint32_t x = 0; x < input.width(); ++x)
		{
			UIColor current = input._pixels.at(y * input.width() + x);
			output << static_cast<uint32_t>(current.r) << '\n' 
							<< static_cast<uint32_t>(current.g) << '\n' 
							<< static_cast<uint32_t>(current.b) << '\n';
		}
	}

	output.close();
}


void Image::exportToPNG(const Image &input, const std::string &path)
{
	uint32_t channels = 4;
	stbi_write_png(path.c_str(), input.width(), input.height(), channels, input._pixels.data(), input.width() * channels);
}

void Image::fromRaw(Image &image, const std::vector<UIColor> &rawData)
{
	image._pixels = rawData;
}

uint32_t Image::width() const
{
	return this->_extent.w;
}

uint32_t Image::height() const
{
	return this->_extent.h;
}

UIColor &Image::operator[](Index2D index)
{
	return this->_pixels.at(index.y * this->_extent.w + index.x);
}

const UIColor &Image::operator[](Index2D index) const
{
	return this->_pixels.at(index.y * this->_extent.w + index.x);
}

Image Image::upscale(const Image &input, uint32_t scale)
{
	uint32_t target_width_v = input.width() * scale;
	uint32_t target_height_v = input.height() * scale;	
	uint32_t x_index{0}, y_index{0};
	Image target_image(target_width_v, target_height_v);

	for(y_index = 0; y_index < input.height(); ++y_index)
	{
		for(x_index = 0; x_index < input.width(); ++x_index)
		{
			const UIColor &current = input[Index2D{x_index, y_index}];
			if(current.hex())
			{
				for(uint32_t i = y_index * scale; i < ((y_index + 1) * scale); ++i)
				{
					for(uint32_t j = x_index * scale; j < ((x_index + 1) * scale); ++j)
						target_image[Index2D{j, i}] = current;
				}
			}
		}
	}

	return target_image;
}