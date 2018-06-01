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
    float       m_reflect;
    float       m_refract;
    bool        m_transparent;

  public:
    Sphere(const Vec3f &center, float radius, const Color &color,
        const float &reflect, const float &refract, const bool transparent);
    ~Sphere();


    bool intersect(const Ray &ray, float &dist);
    void computeColorNormal(const Ray &ray, float dist, MaterialPoint &caracteristics);
    bool transparent() const;
};

#endif
