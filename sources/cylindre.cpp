#include <cmath>
#include <iostream>

#include "cylindre.h"

Cylindre::Cylindre(const Vec3f &base, const Vec3f &direction, const float &height,
    const float &radius, const Color &color, const float &reflect) :
  m_base(base),
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
  float b = (ray.origin() - m_base).vectorial(m_direction) 
    * ray.direction().vectorial(m_direction) * 2;
  float c = (ray.origin() - m_base).vectorial(m_direction)
    * (ray.origin() - m_base).vectorial(m_direction)
    - m_radius * m_radius * m_direction.norm2();
  float delta = b * b - 4 * a * c;

  if (delta < 0)
    return false;
  float sqdelta = sqrt(delta);
  float t1 = (-b + sqdelta) / (2 * a);
  float t2 = (-b - sqdelta) / (2 * a);
  dist = t2;
  float dist_max_sq = pow((ray.origin() + ray.direction() * dist - m_base).norm(), 2)
    - m_radius * m_radius;
  if (sqrt(dist_max_sq) > m_height)
  {
    dist = t1;
    dist_max_sq = pow((ray.origin() + ray.direction() * dist - m_base).norm(), 2)
      - m_radius * m_radius;
    if (sqrt(dist_max_sq) > m_height)
      return false;
  }
  return true;
}

void Cylindre::computeColorNormal(const Ray &ray, float dist, MaterialPoint &mp)
{
  Vec3f intersect = ray.origin() + ray.direction() * dist;
  Vec3f center_intersect = m_base + m_direction 
    * (pow((ray.origin() + ray.direction() * dist - m_base).norm(), 2) - m_radius * m_radius);
  mp.normal = intersect - center_intersect;
  mp.normal.normalize();
  mp.color = m_color;
  mp.reflect = m_reflect;
}
