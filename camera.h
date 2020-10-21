#pragma once

#include "ray.h"
#define M_PI 3.145

class camera
{
public:
  camera(float vfov, float aspect) // vfov: top to bottom [deg]
  {
    float theta = vfov * M_PI / 180.0;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    bottom_left =  vec3(-half_width,-half_height,-1.0);
    horiz = vec3(2*half_width, 0.0, 0.0);
    vert = vec3(0.0, 2*half_height, 0.0);
    origin = vec3(0.0, 0.0, 0.0);
  }
  ray get_ray(float u, float v) { return ray(origin, bottom_left + u * horiz + v * vert); }

  vec3 origin;
  vec3 bottom_left;
  vec3 horiz;
  vec3 vert;
};