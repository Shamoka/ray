#ifndef         __SIMPLE_SCENE_H__
#define         __SIMPLE_SCENE_H__

#include <vector>

#include "primitive.h"
#include "ray.h"

class   SimpleScene
{
  private:
    std::vector<Primitive*>      m_primitives;

  public:
    SimpleScene();
    ~SimpleScene();

    Primitive   *getPrimitive(unsigned long index);
    Primitive   *removePrimitive(unsigned long index);
    long        getFirstCollision(const Ray &ray, float &dist);
    bool        addPrimitive(Primitive *primitive);
};

#endif
