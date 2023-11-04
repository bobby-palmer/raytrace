#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

int main() {

  // World objects

  hittable_list world;
  world.add(make_shared<sphere>(point3(0,     0,  -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
  world.add(make_shared<sphere>(point3(1, 0, -2), 0.5));
  // Rendering

  camera cam;

  cam.image_width = 400;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.samples_per_pixel = 100;

  cam.render(world);
}
