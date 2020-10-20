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
  metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 reflected = reflect(Normalize(r_in.dir()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return true;
  }
  vec3 albedo;
  float fuzz;
};

//////////////// DIELECTRIC (non electric) e.g. Glass ////////////////
// typically air = 1, glass = 1.3 - 1.7, diamond = 2.4
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
  vec3 uv = Normalize(v);
  float dt = Dot(uv, n);
  float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0) {
    refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    return true;
  }
  else {
    return false;
  }
};

// improved model, refraction changes with incident angle
float schlick(float cosine, float ref_idx) {
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class dielectric : public material {
public:
  dielectric(float ri) : ref_idx(ri) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.dir(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0, 1.0, 1.0);
    vec3 refracted;
    float reflect_prob;
    float cosine;
    if (Dot(r_in.dir(), rec.normal) > 0) {
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
      cosine = ref_idx * Dot(r_in.dir(), rec.normal) / Length(r_in.dir());
    }
    else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -Dot(r_in.dir(), rec.normal) / Length(r_in.dir());
    }
    if (refract(r_in.dir(), outward_normal, ni_over_nt, refracted))
    {
      reflect_prob = schlick(cosine,ref_idx);
    }
    else
    {
      scattered = ray(rec.p, refracted);
      reflect_prob = 1.0;
    }
    if (rand_f() < reflect_prob)
    {
      scattered = ray(rec.p, reflected);
    }
    else
    {
      scattered = ray(rec.p, refracted);
    }
    return true;
  }
  float ref_idx;
};
