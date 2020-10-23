#pragma once

#include "ray.h"
#define M_PI 3.145

class camera
{
public:
  camera(vec3 pos, vec3 lookat, vec3 up, float vfov, float aspect) // vfov: top to bottom [deg]
  {
    vec3 u, v, w;
    origin = pos;
    w = Normalize(pos - lookat);
    u = Normalize(Cross(up, w));
    v = Cross(w, u); // this is not equal vup!
    float theta = vfov * M_PI / 180.0;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    bottom_left = origin - half_width * u - half_height * v - w;
//    bottom_left = vec3(-half_width,-half_height,-1.0);
    horiz = 2*half_width*u;
    vert = 2*half_height*v;
  }
  ray get_ray(float s, float t) { return ray(origin, bottom_left + s * horiz + t * vert - origin); }

  vec3 origin;
  vec3 bottom_left;
  vec3 horiz;
  vec3 vert;
};