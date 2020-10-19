#ifndef VEC3F_HXX
#define VEC3F_HXX

#include <math.h>
#include <assert.h>
//#include <iostream>
//#include <fstream>

class vec3 
{
public:
  float x,y,z;

  vec3() {};
  vec3(float x,float y, float z) : x(x), y(y), z(z) {};

  //! Array operator: just for convenience: @f$ a[0]==a.x, a[1]==a.y, a[2]==a.z @f$ 
  /*! be careful : a[0] is often slower than accessing a.x !
   * Also assert that @f$  0 <= i < 3 @f$ 
   */
  inline const float &operator[](const int i) const { return *(&x+i); }; 

  //! Array operator: just for convenience: @f$  a[0]==a.x, a[1]==a.y, a[2]==a.z @f$ ...
  /*! be careful : a[0] is often slower than accessing a.x !
   * Also assert that @f$  0 <= i < 3 @f$  
   */
  inline float &operator[](const int i) { return *(&x+i); }; //((float *)(this))[i]; };

  inline vec3 &operator=(const vec3 &b) { x = b.x; y = b.y; z = b.z; return *this;};
};

#define Epsilon 1E-5
#define Infinity HUGE_VAL

  /*! dot product */
inline float Dot(const vec3 &a, const vec3 &b) { return a.x*b.x+a.y*b.y+a.z*b.z; };

  /*! component-wise product */
inline vec3 Product(const vec3 &a, const vec3 &b) { return vec3(a.x*b.x,a.y*b.y,a.z*b.z); };

  /*! vector product */
inline vec3 Cross(const vec3 &a, const vec3 &b)
{ return vec3(a.y*b.z-a.z*b.y,
	    a.z*b.x-a.x*b.z,
	    a.x*b.y-a.y*b.x); };

inline vec3 operator-(const vec3 &v) { return vec3(-v.x,-v.y,-v.z); };

inline float Length(const vec3 &v) { return sqrt(Dot(v,v)); };

  /*! still undocumented */
inline vec3 operator*(const float f, const vec3 &v) { return vec3(f*v.x, f*v.y, f*v.z); };

  /*! still undocumented */
inline vec3 operator*(const vec3 &v, const float f) { return vec3(f*v.x, f*v.y, f*v.z); };

  /*! still undocumented */
inline void operator*=(vec3 &v, const float f) { v.x *= f; v.y*=f; v.z*=f; };

  /*! still undocumented */
inline void operator*=(vec3 &v, const vec3 &f) { v.x *= f.x; v.y*=f.y; v.z*=f.z; };

  /*! still undocumented */
inline vec3 operator/(const vec3 &v, const float f) { return (1/f)*v; };

  /*! still undocumented */
inline void operator/=(vec3 &v, const float f) { v *= (1/f); };

  /*! still undocumented */
inline vec3 operator+(const vec3 &a, const vec3 &b) { return vec3(a.x+b.x, a.y+b.y, a.z+b.z); };
inline void operator+=(vec3& a, const vec3& b) { a.x += b.x; a.y += b.y; a.z += b.z; };
inline vec3 operator+(const vec3& a, const float& f) { return vec3(a.x + f, a.y + f, a.z + f); }; // does this make sense?

  /*! still undocumented */
inline vec3 operator-(const vec3 &a, const vec3 &b) { return vec3(a.x-b.x, a.y-b.y, a.z-b.z); };

//inline void Normalize(vec3 &v) { v *= (1.f/Length(v)); };
inline vec3 Normalize(const vec3& v) { return v * (1.f / Length(v)); };

//inline ostream &operator<<(ostream &o,const Vec3f &v)
//{ o << "(" << v.x << "," << v.y << "," << v.z << ")"; return o; };


#endif


