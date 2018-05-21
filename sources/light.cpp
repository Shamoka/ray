#include "light.h"

Light::Light(const Vec3f &center, const Color &color) :
  m_center(center), m_color(color)
{}

Light::~Light()
{}

Color Light::computeColor(const Ray &ray, float dist)
{
  return m_color * (1. / (dist * dist));
}

const Vec3f &Light::center() const
{
  return m_center;
}
