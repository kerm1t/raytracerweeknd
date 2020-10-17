#pragma once
#include "vec3f.hxx"

class ray
{
  vec3 A, B;
public:
  ray() {}; // constructor
  ray(const vec3& a, const vec3& b) { A = a; B = b; }
  vec3 origin() const { return A; } // const function, i.e. not allowed ray.origin = ...
  vec3 dir() const { return B; }
  vec3 point_at_param(float t) { return A + t * B; }
};
