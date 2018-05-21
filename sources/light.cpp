#include "light.h"

Light::Light(Vec3f center, Color color) :
  m_center(center), m_color(color)
{}

Light::~Light()
{}

Color Light::computeColor(const Ray &ray, float dist)
{
  return m_color * (1. / (dist * dist));
}

const Vec3f Light::getCenter() const
{
  return m_center;
}
