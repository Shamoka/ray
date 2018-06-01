#ifndef         __PLANE_H__
#define         __PLANE_H__

#include "color.h"
#include "vec3f.h"
#include "ray.h"
#include "primitive.h"

class Plane : public virtual Primitive
{
  private:
    Vec3f       m_normal;
    Vec3f       m_point;
    Color       m_color;
    float       m_reflect;
    float       m_refract;
    bool        m_transparent;

  public:
    Plane(const Vec3f &normal, const Vec3f &point, const Color &color,
        const float &reflect, const float &refract, const bool transparent);
    ~Plane();

    bool intersect(const Ray &ray, float &dist);
    void computeColorNormal(const Ray &ray, float dist, MaterialPoint &caracteristics);
    bool transparent() const;
};

#endif
