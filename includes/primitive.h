#ifndef         __PRIMITIVE_H__
#define         __PRIMITIVE_H__

#include "ray.h"
#include "color.h"
#include "vec3f.h"

typedef struct  s_materialPoint
{
  Vec3f         normal;
  Color         color;
  float         reflect;
}               MaterialPoint;

class Primitive
{
  public:
    Primitive();
    virtual ~Primitive();

    virtual bool intersect(const Ray &ray, float &dist) = 0;
    virtual void computeColorNormal(const Ray &ray, float dist, 
        MaterialPoint &caracteristics) = 0;
};

#endif
