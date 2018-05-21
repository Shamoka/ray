#ifndef         __LIGHT_H__
#define         __LIGHT_H__

#include "vec3f.h"
#include "color.h"
#include "ray.h"

class Light
{
  private:
    Vec3f       m_center;
    Color       m_color;

  public:
    Light(Vec3f center, Color color);
    ~Light();
    Color       computeColor(const Ray &ray, float dist);
    const Vec3f getCenter() const;
};

#endif
