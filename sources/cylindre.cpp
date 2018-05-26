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
  float a = ray.direction().x() * ray.direction().x()
    + ray.direction().y() * ray.direction().y();
  float b = 2 * (ray.origin().x() * ray.direction().x()
      - ray.direction().x() * m_base.x()
      + ray.origin().y() * ray.direction().y()
      - ray.direction().y() * m_base.y());
  float c = ray.origin().y() * ray.origin().y()
    + ray.origin().x() * ray.origin().x()
    - 2 * ray.origin().x() * m_base.x()
    - 2 * ray.origin().y() * m_base.y()
    - m_radius * m_radius;
  float delta = b * b - 4 * a * c;

  if (delta < 0)
    return false;
  float sqdelta = sqrt(delta);
  float t1 = (-b + sqdelta) / (2 * a);
  float t2 = (-b - sqdelta) / (2 * a);
  float height1 = ray.origin().z() + t1 * ray.direction().z() - m_base.z();
  float height2 = ray.origin().z() + t2 * ray.direction().z() - m_base.z();
  float height;
  if (height1 < 0)
  {
    height = height2;
    dist = t2;
  }
  else
  {
    height = height1;
    dist = t1;
  }
  if (height > m_height || height < 0)
    return false;
  return true;
}

void Cylindre::computeColorNormal(const Ray &ray, float dist, MaterialPoint &mp)
{
  Vec3f intersect = ray.origin() + ray.direction() * dist;
  Vec3f center_intersect = m_base;
  center_intersect.setZ(m_base.z() + ray.origin().z() + ray.direction().z() * dist);
  mp.normal = center_intersect - intersect;
  mp.normal.normalize();
  mp.color = m_color;
  mp.reflect = m_reflect;
}
