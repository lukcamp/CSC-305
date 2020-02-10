#include "assignment.hpp"
#include <stdio.h>

int main()
{
	// Your code here.
	constexpr std::size_t image_width{ 600 };
	constexpr std::size_t image_height{ 600 };
	constexpr Colour background{ 0,0,0 };
	constexpr Sphere s{ {50,50,-100}, 50, {1,0,0} };
	constexpr Sphere s1{ {254, 354, -100}, 40, {0.3,0.3,0.3} };
	constexpr Sphere s2{ {200,180,-100}, 85 , {0,1,0} };
	constexpr Sphere s3{ {575,25,-100}, 25 , {1,1,0} };
	constexpr Sphere s4{ {100,500,-100}, 30 , {0,0,1} };
	constexpr Sphere s5{ {50,550,-200}, 50 , {1,1,1} };
	constexpr Plane p{ {300,100,100}, {0,1,0}, {0.5,0,1} };
	constexpr Plane p1{ {200,0,100}, {1,0,0}, {1,0,1} };



	atlas::math::Ray<atlas::math::Vector> ray{ { 0,0,0 }, { 0,0,-1 } };

	std::vector<Colour> image{ image_width * image_height };
	ShadeRec trace_data{};

	for (std::size_t y{ 0 }; y < image_height; y++)
	{
		for (std::size_t x{ 0 }; x < image_width; x++) 
		{
			ray.o = { x + 0.5f, y + 0.5f, 0 };

			if (!s.hit(ray, trace_data) && !s1.hit(ray, trace_data) && !s2.hit(ray, trace_data) && !s3.hit(ray, trace_data) && !s4.hit(ray, trace_data) && !s5.hit(ray, trace_data) && !p.hit(ray, trace_data) && !p1.hit(ray, trace_data) )
			{
				trace_data.colour = background;

			}

			image[x + y * image_height] = trace_data.colour;
		}
	}

	saveToFile("H:/Documents/csc305/a1/images/output.bmp",
		image_width, image_height, image);

    return 0;
}

void saveToFile(std::string const& filename,
                std::size_t width,
                std::size_t height,
                std::vector<Colour> const& image)
{
    std::vector<unsigned char> data(image.size() * 3);

    for (std::size_t i{0}, k{0}; i < image.size(); ++i, k += 3)
    {
        Colour pixel = image[i];
        data[k + 0]  = static_cast<unsigned char>(pixel.r * 255);
        data[k + 1]  = static_cast<unsigned char>(pixel.g * 255);
        data[k + 2]  = static_cast<unsigned char>(pixel.b * 255);
    }

    stbi_write_bmp(filename.c_str(),
                   static_cast<int>(width),
                   static_cast<int>(height),
                   3,
                   data.data());
}
