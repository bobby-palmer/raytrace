#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "hittable.h"
class hit_record;

class material {
public:
virtual ~material() = default;

virtual bool scatter(
  const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
  lambertian(const color& a) : albedo(a) {}

  virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();

    // catch degenerate scatter direction
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
private:
  color albedo;
};

class metal : public material {
public:
  metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

  virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
    vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz*random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }
private:
  color albedo;
  double fuzz;
};

class dielectric : public material {
public:
  dielectric(double index_of_refraction) : ir(index_of_refraction) {}

  virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
      attenuation = color(1.0, 1.0, 1.0);
      double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

      vec3 unit_direction = unit_vector(ray_in.direction());
      vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);

      scattered = ray(rec.p, refracted);
      return true;
  }
private:
  double ir;
};
