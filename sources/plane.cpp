#include "plane.h"

Plane::Plane(const Vec3f &normal, const Vec3f &point, const Color &color) :
  m_normal(normal), m_point(point), m_color(color)
{}

Plane::~Plane()
{}

bool Plane::intersect(const Ray &ray, float &dist)
{
  float a = (m_point - ray.origin() + ray.direction()).dot(m_normal);
  float b = ray.direction().dot(m_normal);

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
  mp.reflect = Color(0.2, 0.2, 0.2);
}
