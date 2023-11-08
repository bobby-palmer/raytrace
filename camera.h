#pragma once

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "vec3.h"

class camera {
  public:
  double aspect_ratio      = 1.0; // width / height
  int    image_width       = 100;
  int    samples_per_pixel = 10;

  void render(hittable& world) {
    initialize();
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
      std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
      for (int i = 0; i < image_width; ++i) {
        color pixel_color( 0, 0, 0);
        for (int samples = 0; samples < samples_per_pixel; ++samples) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world);
        }
        write_color(std::cout, pixel_color, samples_per_pixel);
      }
    }

    std::clog << "\rDone.                 \n";
  }

  private:
  int image_height;
  point3 camera_center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;

  void initialize() {
    // Calculate the image height, and ensure that it's at least 1.
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    camera_center = point3( 0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

    
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  color ray_color(const ray& r, const hittable& world) const {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
      vec3 direction = random_on_hemisphere(rec.normal);
      return 0.5 * ray_color(ray(rec.p, direction), world);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
  }

  ray get_ray(int i,int j) {
    auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto direction = pixel_sample - camera_center;

    return ray(camera_center, direction);
  }

  vec3 pixel_sample_square() {
    auto px = -0.5 + random_double();
    auto py = -0.5 + random_double();

    return (px * pixel_delta_u) + (py * pixel_delta_v);
  }
}; // camera
