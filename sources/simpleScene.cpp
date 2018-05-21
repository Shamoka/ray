#include <iterator>
#include <limits>
#include <algorithm>
#include <iostream>

#include "simpleScene.h"

SimpleScene::SimpleScene() :
  m_primitives()
{}

SimpleScene::~SimpleScene()
{
  for (std::vector<Primitive*>::const_iterator it = this->m_primitives.begin();
      it != this->m_primitives.end(); ++it)
  {
    delete *it;
  }
}

Primitive *SimpleScene::getPrimitive(unsigned long index)
{
  return this->m_primitives[index];
}

Primitive *SimpleScene::removePrimitive(unsigned long index)
{
  std::vector<Primitive*>::iterator it = this->m_primitives.begin();
  std::advance(it, index);
  Primitive *primitive = *it;
  this->m_primitives.erase(it);
  return primitive;
}

long SimpleScene::getFirstCollision(const Ray &ray, float &dist)
{
  float         min_dist = std::numeric_limits<float>::max();
  long          min_primitive = -1;

  for (std::vector<Primitive*>::const_iterator it = this->m_primitives.begin();
      it != this->m_primitives.end(); ++it)
  {
    float currentDist;

    if ((*it)->intersect(ray, currentDist) && currentDist > 0.1f && currentDist < min_dist)
    {
      min_primitive = it - this->m_primitives.begin();
      min_dist = currentDist;
    }
  }

  if (min_primitive == -1)
    return -1;
  dist = min_dist;
  return min_primitive;
}

bool SimpleScene::addPrimitive(Primitive *primitive)
{
  if (std::find(this->m_primitives.begin(), this->m_primitives.end(),
        primitive) != this->m_primitives.end())
    return false;
  this->m_primitives.push_back(primitive);
  return true;
}
