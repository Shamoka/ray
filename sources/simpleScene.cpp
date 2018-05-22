#include <iterator>
#include <limits>
#include <algorithm>
#include <iostream>

#include "simpleScene.h"
#include "light.h"

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

    if ((*it)->intersect(ray, currentDist) && currentDist > 0.01f && currentDist < min_dist)
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

bool SimpleScene::addLight(Light *l)
{
  if (std::find(this->m_lights.begin(), this->m_lights.end(), l) != this->m_lights.end())
    return false;
  this->m_lights.push_back(l);
  return true;
}

const Color SimpleScene::computeColor(const Vec3f &center, const MaterialPoint &mp)
{
  Color         t_color(0, 0, 0);

  for (std::vector<Light*>::const_iterator it = m_lights.begin();
      it != m_lights.end(); ++it)
  {
    Vec3f       path = (*it)->center() - center;
    float       pathSize = path.norm();
    path.normalize();
    Ray         ray(center, path);

    if (testCollision(ray, pathSize))
      continue;

    float cosphi = path * mp.normal;
    if (cosphi < 0.01f)
      cosphi = - cosphi;
    t_color += mp.color * cosphi * (*it)->computeColor(ray, pathSize);
  }
  return t_color;
}

bool SimpleScene::testCollision(const Ray &ray, float dist)
{
  for (std::vector<Primitive*>::const_iterator it = m_primitives.begin();
      it != m_primitives.end(); ++it)
  {
    float t_dist;
    if ((*it)->intersect(ray, t_dist) && t_dist > 0.01f && t_dist < dist)
      return true;
  }
  return false;
}
