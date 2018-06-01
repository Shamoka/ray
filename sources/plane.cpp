#include "plane.h"

Plane::Plane(const Vec3f &normal, const Vec3f &point, const Color &color,
    const float &reflect, const float &refract, const bool transparent) :
  m_normal(normal),
  m_point(point),
  m_color(color),
  m_reflect(reflect),
  m_refract(refract),
  m_transparent(transparent)
{}

Plane::~Plane()
{}

bool Plane::intersect(const Ray &ray, float &dist)
{
  float a = (m_point - ray.origin() + ray.direction()) * m_normal;
  float b = ray.direction() * m_normal;

  if (b < 0.001f)
  {
    if (a < 0.001f)
      return false;
    dist = 0;
    return true;
  }
  dist = a / b;
  return true;
}

void Plane::computeColorNormal(const Ray &ray, float dist, MaterialPoint &mp)
{
  mp.normal = m_normal;
  mp.color = m_color;
  mp.refract = m_refract;
  mp.reflect = m_reflect;
}

bool Plane::transparent() const
{
  return m_transparent;
}
