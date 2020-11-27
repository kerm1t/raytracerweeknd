#pragma once
#include "hitable.h"
#include "material.h"

class sphere: public hitable
{
public:
  sphere() {};
  sphere(vec3 cen, float r, material* p_m): center(cen), radius(r), mat_ptr(p_m) {};
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  vec3 center;
  float radius;
  material* mat_ptr;
};
/* t_min and t_max limit the length of intersection space */
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
  vec3 oc = r.origin() - center; // ray origin - circle center
  float a = Dot(r.dir(), r.dir());
  float b = Dot(oc, r.dir());
  float c = Dot(oc, oc) - radius * radius;
  float discriminant = b * b - a * c; // under the sqrt: b^2-4ac
  if (discriminant > 0) // 1 or 2 solutions (discriminant is different, s.above)
  {
    float temp = (-b - sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_param(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;
      return true;
    }
    temp = (-b + sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_param(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;
      return true;
    }
  }
  return false;
}
