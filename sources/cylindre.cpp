#include <cmath>
#include <iostream>

#include "cylindre.h"

Cylindre::Cylindre(const Vec3f &center, const Vec3f &direction, const float &height,
    const float &radius, const Color &color, const float &reflect) :
  m_center(center),
  m_direction(direction),
  m_height(height),
  m_radius(radius),
  m_color(color),
  m_reflect(reflect)
{}

Cylindre::~Cylindre()
{}

bool Cylindre::intersect(const Ray &ray, float &dist)
{
  float a = ray.direction().vectorial(m_direction).norm2();
  float b = (ray.origin() - m_center).vectorial(m_direction) 
    * ray.direction().vectorial(m_direction) * 2;
  float c = (ray.origin() - m_center).vectorial(m_direction)
    * (ray.origin() - m_center).vectorial(m_direction)
    - m_radius * m_radius * m_direction.norm2();
  float delta = b * b - 4 * a * c;

  if (delta < 0)
    return false;
  float sqdelta = sqrt(delta);
  float t1 = (-b + sqdelta) / (2 * a);
  float t2 = (-b - sqdelta) / (2 * a);
  if (t2 < 0.01f)
  {
    float tmp = t1;
    t1 = t2;
    t2 = tmp;
  }
  dist = t2;
  float dist_max_sq = pow((ray.origin() + ray.direction() * dist - m_center).norm(), 2)
    - m_radius * m_radius;
  if (sqrt(dist_max_sq) > m_height / 2)
  {
    dist = t1;
    dist_max_sq = pow((ray.origin() + ray.direction() * dist - m_center).norm(), 2)
      - m_radius * m_radius;
    if (sqrt(dist_max_sq) > m_height / 2)
      return false;
  }
  return true;
}

void Cylindre::computeColorNormal(const Ray &ray, float dist, MaterialPoint &mp)
{
  Vec3f m = ray.origin() + ray.direction() * dist;
  mp.normal = m_direction * (((m_center - m) * m_direction) / m_direction.norm2());
  mp.normal.normalize();
  mp.color = m_color;
  mp.reflect = m_reflect;
}
