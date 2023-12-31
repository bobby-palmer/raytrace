#pragma once

#include "rtweekend.h"
#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
  public:
    double e[3];
    
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }
    
    vec3& operator+=(const vec3& v) {
      e[0] += v[0];
      e[1] += v[1];
      e[2] += v[2];
      return *this;
    }

    vec3& operator*=(double t) {
      e[0] *= t;
      e[1] *= t;
      e[2] *= t;
      return *this;
    }

    vec3& operator/=(double t) {
      return *this *= (1 / t);
    }
    
    double length() const {
      return sqrt(length_squared());
    }

    double length_squared() const {
      return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const {
      auto s = 1e-8;
      return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }
    static vec3 random() {
      return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
      return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
}; // vec3()

using point3 = vec3;
using color = vec3;
// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& p) {
  return out << p[0] << ' ' << p[1] << ' ' << p[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u) += v;
}

inline vec3 operator-(const vec3& u, const vec3& v) {
  return -v += u;
}

inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u[0] * v[0], u[1]* v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3& v) {
  return vec3(v) *= t;
}

inline vec3 operator*(const vec3& v, double t) {
  return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
  return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
  return u[0] * v[0] +
         u[1] * v[1] +
         u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
  return vec3(
    u[1] * v[2] - u[2] * v[1],
    u[2] * v[0] - u[0] * v[2],
    u[0] * v[1] - u[1] * v[0]
  );
}

inline vec3 unit_vector(const vec3& v) {
  return v / v.length();
}

inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.length_squared() < 1) {
      return p;
    }
  }
}

inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3& normal) {
  auto v = random_unit_vector();
  if (dot(normal, v) > 0.0)
    return v;
  else
    return -v;
}

vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
inline vec3 random_in_unit_disk() {
  while (true) {
      auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
      if (p.length_squared() < 1)
          return p;
  }
}
