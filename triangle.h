#pragma once
#include "hitable.h"
#include "material.h"

class triangle : public hitable
{
public:
  triangle() {};
  triangle(vec3 a1, vec3 a2, vec3 a3, material* p_m) : a(a1), b(a2),c(a3), mat_ptr(p_m) {};
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  vec3 a,b,c;
  material* mat_ptr;
};

// Moeller–Trumbore intersection
bool triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
//  vec3 oc = r.origin() - center; // ray origin - circle center

  const float EPSILON = 0.0000001;
  vec3 edge1, edge2, h, s, q;
  float _a, f, u, v;
  edge1 = b - a;
  edge2 = c - a;
  h = Cross(r.dir(), edge2);
  _a = Dot(edge1,h);
  if (_a > -EPSILON && _a < EPSILON)
    return false;    // This ray is parallel to this triangle.
  f = 1.0 / _a;
  s = r.origin() - a;
  u = f * Dot(s,h);
  if ((u < 0.0) || (u > 1.0))
    return false;
  q = Cross(s,edge1);
  v = f * Dot(r.dir(),q);
  if ((v < 0.0) || (u + v > 1.0))
    return false;
  // At this stage we can compute t to find out where the intersection point is on the line.
  float t = f * Dot(edge2,q);
  if (t > EPSILON) // ray intersection
  {
    rec.t = t; // length of ray.direction at intersection pt.
    rec.p = r.point_at_param(rec.t); // r.origin() + r.dir() * t;
    rec.normal = Cross(edge1,edge2); // ???
    rec.mat_ptr = mat_ptr;
    return true;
  }
  else // This means that there is a line intersection but not a ray intersection.
    return false;
}

/*
bool RayIntersectsTriangle(Vector3D rayOrigin,
                           Vector3D rayVector,
                           Triangle* inTriangle,
                           Vector3D& outIntersectionPoint)
{
    const float EPSILON = 0.0000001;
    Vector3D vertex0 = inTriangle->vertex0;
    Vector3D vertex1 = inTriangle->vertex1;
    Vector3D vertex2 = inTriangle->vertex2;
    Vector3D edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = rayVector.crossProduct(edge2);
    a = edge1.dotProduct(h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = rayOrigin - vertex0;
    u = f * s.dotProduct(h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = s.crossProduct(edge1);
    v = f * rayVector.dotProduct(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.dotProduct(q);
    if (t > EPSILON) // ray intersection
    {
        outIntersectionPoint = rayOrigin + rayVector * t;
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}
*/