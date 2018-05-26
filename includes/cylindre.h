#ifndef         __CYLINDRE_H__
#define         __CYLINDRE_H__

#include "vec3f.h"
#include "color.h"
#include "ray.h"
#include "primitive.h"

class Cylindre : public virtual Primitive
{
  private:
    Vec3f       m_base;
    float       m_height;
    float       m_radius;
    Color       m_color;
    float       m_reflect;

  public:
    Cylindre(const Vec3f &base, const float &height, const float &radius,
        const Color &color, const float &reflect);
    ~Cylindre();

    bool intersect(const Ray &ray, float &dist);
    void computeColorNormal(const Ray &ray, float dist, MaterialPoint &caracteristics);
};

#endif