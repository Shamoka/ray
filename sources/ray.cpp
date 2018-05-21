#include "ray.h"

Ray::Ray(const Vec3f &origin, const Vec3f &direction) :
  m_origin(origin), m_direction(direction)
{}

Ray::~Ray()
{}

const Vec3f &Ray::origin() const { return this->m_origin; }

Vec3f &Ray::origin() { return this->m_origin; }

const Vec3f &Ray::direction() const { return this->m_direction; }

Vec3f &Ray::direction() { return this->m_direction; }
