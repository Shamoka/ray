#include <cmath>

#include "sphere.h"

Sphere::Sphere(const Vec3f &center, float radius, const Color &color, const float &reflect) :
  m_center(center), m_radius(radius), m_color(color), m_reflect(reflect)
{}

Sphere::~Sphere()
{}

bool Sphere::intersect(const Ray &ray, float &dist)
{
  Vec3f vector = ray.origin() - m_center;
  float b = -(ray.direction() * vector);
  float c = vector.norm2() - m_radius * m_radius;
  float delta = (b * b - c);

  if (delta < 0.f)
    return false;
  float disc = sqrt(delta);
  if ((dist = b - disc) < 0.01)
    dist = b + disc;
  return true;
}

void Sphere::computeColorNormal(const Ray &ray, float dist, MaterialPoint &mp)
{
  Vec3f         collide(ray.origin() + ray.direction() * dist);

  mp.normal = collide - m_center;
  mp.normal.normalize();
  mp.color = m_color;
  mp.reflect = m_reflect;
}

