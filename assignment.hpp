#pragma once

#include <atlas/core/Float.hpp>
#include <atlas/math/Math.hpp>
#include <atlas/math/Ray.hpp>

#include <fmt/printf.h>
#include <stb_image.h>
#include <stb_image_write.h>

#include <vector>

using Colour = atlas::math::Vector;

void saveToFile(std::string const& filename,
                std::size_t width,
                std::size_t height,
                std::vector<Colour> const& image);

// Your code here.
struct ShadeRec
{
	Colour colour;
	float t;
};




class Plane
{
public:
	/*
	Plane(void);

	Plane(const atlas : math:Point point, const atlas::math::Normal n);

	virtual bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, double& t, ShadeRec& trace_data) const;
	*/

	constexpr Plane(atlas::math::Point p0, atlas::math::Normal normal, Colour colour):
		p0_{ p0 },
		normal_{normal},
		colour_{colour}
	{}
	

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data)const {

		auto o_c{ p0_ - ray.o };
		auto a{ glm::dot(o_c, normal_) };
		float b = 1;
		b = glm::dot(ray.d, normal_);
		auto c{ a / b } ;

		if (c > 0.0001f) {
			
			trace_data.colour = colour_;
			trace_data.t = c;
			return true;
		}
		else {
			return false;
		}

		/*


	

		auto o_c{ p0_ - ray.o };
		auto a{ glm::dot(o_c, normal_) };
		auto b{ glm::dot(ray.d, normal_) };
		auto c{ a/b };

		if (c > 0.0001f) {
			//tmin = c;
			auto x{ glm::dot(c, ray.d) };
			trace_data.t = ray.o + x;
			trace_data.colour = colour_;
			return true;

		}
		else return false;

		/*
		auto o_c{ ray.o - p0_ };
		
		auto denom{ glm::dot(normal_, o_c ) };

		if (denom > 0.0001f) {
			//point minus origin
			auto p_o{ p0_ - ray.o };
			auto up{ glm::dot(p_o, normal_) };
			trace_data.t = up / denom;
			trace_data.colour = colour_;
			return (trace_data.t >= 0);

		}

		*/
		
	}
	
private:
	atlas::math::Point p0_;
	atlas::math::Vector normal_;
	Colour colour_;
};



class Sphere
{
public:
	constexpr Sphere(atlas::math::Point center, float radius, Colour colour):
		center_{center},
		radius_{radius},
		radius_sqr_{radius*radius},
		colour_{colour}
	{}




	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data) const
	{
		auto o_c{ ray.o - center_ };

		auto a{ glm::dot(ray.d, ray.d) };
		auto b{ glm::dot(ray.d, o_c) * 2 };
		auto c{ glm::dot(o_c, o_c) - radius_sqr_ };

		auto roots{ b * b - (4.0f * a * c) };

		if (roots >= 0.0f) {

			

			float temp = ((-b - std::sqrt(roots)) / (2.0f * a));
			if (temp <= 0) {
				return false;
			}
			if (temp < trace_data.t) {
				trace_data.colour = colour_;
				trace_data.t = temp;
				
			}

			//trace_data.colour = colour_;
			/*atlas::math::Vector  norm{ center_ - (ray.d * trace_data.t + ray.o) }; //This code creates a gradient on the sphere
			norm = norm / norm.length;
			atlas::math::Vector light{ 1,1,0 }; 
			trace_data.colour = glm::dot(norm, { 1, 1, 0 }) * colour_;
			*/
			return true;
		}

		return false;
	}


private:
	atlas::math::Point center_;
	float radius_, radius_sqr_;
	Colour colour_;
};