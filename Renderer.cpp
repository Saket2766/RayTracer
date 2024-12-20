#include <iostream>
#include "Renderer.h"
#include "Vec3.h"
#include "Ray.h"
#include "Color.h"

namespace RayTracer {
	double aspect_ratio = 16.0 / 9.0;
	int width = 400;
	int height = int(width / aspect_ratio);
	

	color ray_color(const ray& r) {
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

	void Render() {
		height = (height < 1)? 1 : height;
		
		//Camera
		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (double(width) / height);
		auto camera_center = point3(0, 0, 0);

		//Calculate vectors across the horizontal and down the vertical viewport edges
		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		//Calculate the horizontal and vertical delta vectors
		auto pixel_delta_u = viewport_u / width;
		auto pixel_delta_v = viewport_v / height;

		//Calculate the upper left pixel location
		auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 -viewport_v/2;
		auto pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		std::cout << "P3\n" << width << " " << height << "\n255\n";

		for (int j = 0; j < height; j++) {
			std::clog << "\nScanlines Remaining : " << (height - j) << std::flush;
			for (int i = 0; i < width; i++) {
				auto pixel_center = pixel_00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
				auto ray_direction = pixel_center - camera_center;
				ray r(camera_center, ray_direction);

				color pixel_color = ray_color(r);
				write_color(std::cout, pixel_color);
			}
		}
		std::clog << "\r Done. \n";
	}
}