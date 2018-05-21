#ifndef         __SIMPLE_SCENE_H__
#define         __SIMPLE_SCENE_H__

#include <vector>

#include "primitive.h"
#include "ray.h"
#include "light.h"

class   SimpleScene
{
  private:
    std::vector<Primitive*>     m_primitives;
    std::vector<Light*>         m_lights;

  public:
    SimpleScene();
    ~SimpleScene();

    Primitive   *getPrimitive(unsigned long index);
    Primitive   *removePrimitive(unsigned long index);
    long        getFirstCollision(const Ray &ray, float &dist);
    bool        addPrimitive(Primitive *primitive);
    bool        addLight(Light *light);
    bool        testCollision(const Ray &ray, float dist);
    const Color computeColor(const Vec3f &center, const MaterialPoint &mp);
};

#endif
