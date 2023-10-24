#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

//Using

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  static std::mt19937 gen;
  return dist(gen);
}

// common headers

#include "ray.h"
#include "vec3.h"
#include "interval.h"
