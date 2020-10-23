#pragma once

#include "ray.h"
#define M_PI 3.145

vec3 random_in_unit_disk() {
  vec3 p;
  do {
    p = 2.0 * vec3(rand_f(), rand_f(), 0) - vec3(1, 1, 0);
  } while (Dot(p, p) >= 1.0);
  return p;
}
class camera
{
public:
  camera(vec3 pos, vec3 lookat, vec3 up, float vfov, float aspect, float aperture, float focus_dist) // vfov: top to bottom [deg]
  {
    origin = pos;
    w = Normalize(pos - lookat);
    u = Normalize(Cross(up, w));
    v = Cross(w, u); // this is not equal vup!
    lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180.0;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    bottom_left = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist*w;
    horiz = 2*half_width*focus_dist*u;
    vert = 2*half_height*focus_dist*v;
  }
  ray get_ray(float s, float t) {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x + v * rd.y;
    return ray(origin+offset, bottom_left + s * horiz + t * vert - origin-offset);
  }

  vec3 origin;
  vec3 u, v, w;
  vec3 bottom_left;
  vec3 horiz;
  vec3 vert;
  float lens_radius;
};