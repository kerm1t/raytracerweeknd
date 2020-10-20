#pragma once

#include "ray.h"
#include "stdlib.h" // rand()

class material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

inline float rand_f(void) { return rand() / 32767.0; };

//////////////// LAMBERTIAN ////////////////
vec3 random_in_unit_sphere()
{
  vec3 p;
  do {
    p = 2.0 * vec3(rand_f(), rand_f(), rand_f()) - vec3(1, 1, 1);
  } while (SquaredLength(p) >= 1.0);
  return p;
}

class lambertian : public material {
public:
  lambertian(const vec3& a) : albedo(a) {}
  virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
  }
  vec3 albedo;
};

//////////////// METAL ////////////////
vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * Dot(v, n) * n;
}

class metal : public material {
public:
  metal(const vec3& a) : albedo(a){}
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 reflected = reflect(Normalize(r_in.dir()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  }
  vec3 albedo;
};