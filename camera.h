#pragma once

#include "ray.h"

class camera
{
public:
  camera()
  {
    bottom_left =  vec3(-2.0, -1.5, -1.0);
    horiz = vec3(4.0, 0.0, 0.0);
    vert = vec3(0.0, 3.0, 0.0);
    origin = vec3(0.0, 0.0, 0.0);
  }
  ray get_ray(float u, float v) { return ray(origin, bottom_left + u * horiz + v * vert); }

  vec3 origin;
  vec3 bottom_left;
  vec3 horiz;
  vec3 vert;
};