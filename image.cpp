#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

int main() {

  // Image

  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // World objects
  hittable_list world;
  world.add(make_shared<sphere>(point3(0,      0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  camera().render(world);
}
