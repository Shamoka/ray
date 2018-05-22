#ifndef         __SPHERE_H__
#define         __SPHERE_H__

#include "vec3f.h"
#include "color.h"
#include "primitive.h"

class Sphere : public virtual Primitive
{
  private:
    Vec3f       m_center;
    float       m_radius;
    Color       m_color;
    Color       m_reflect;

  public:
    Sphere(const Vec3f &center, float radius, const Color &color, const Color &reflect);
    ~Sphere();


    bool intersect(const Ray &ray, float &dist);
    void computeColorNormal(const Ray &ray, float dist, MaterialPoint &caracteristics);
};

#endif
