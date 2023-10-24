#pragma once

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& c) {
  out << static_cast<int>(255.999 * c.x()) << ' '
      << static_cast<int>(255.999 * c.y()) << ' '
      << static_cast<int>(255.999 * c.z()) << '\n';
}
