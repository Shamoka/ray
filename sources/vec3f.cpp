#include <math.h>

#include "vec3f.h"

Vec3f::Vec3f()
{}

Vec3f::Vec3f(float f) :
  m_x(f), m_y(f), m_z(f)
{}

Vec3f::Vec3f(float x, float y, float z) :
  m_x(x), m_y(y), m_z(z)
{}

Vec3f::~Vec3f()
{}

float Vec3f::x() const { return m_x; }

float Vec3f::y() const { return m_y; }

float Vec3f::z() const { return m_z; }

void Vec3f::setX(float f) { m_x = f; }
void Vec3f::setY(float f) { m_y = f; }
void Vec3f::setZ(float f) { m_z = f; }

Vec3f &Vec3f::normalize()
{
  float norm = this->norm();

  if (norm != 0)
  {
    m_x /= norm;
    m_y /= norm;
    m_z /= norm;
  }
  return *this;
}

float Vec3f::norm() const
{
  return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Vec3f::norm2() const
{
  return m_x * m_x + m_y * m_y + m_z * m_z;
}

Vec3f Vec3f::vectorial(const Vec3f &v) const
{
  return Vec3f(m_y * v.z() - m_z * v.y(),
      m_z * v.x() - m_x * v.z(),
      m_x * v.y() - m_y * v.x());
}

Vec3f Vec3f::operator*(const float &f) const
{
  return Vec3f(m_x * f, m_y * f, m_z * f);
}

Vec3f Vec3f::operator/(const float &f) const
{
  return Vec3f(m_x / f, m_y / f, m_z / f);
}

float Vec3f::operator*(const Vec3f &v) const
{
  return m_x * v.x() + m_y * v.y() + m_z * v.z();
}

Vec3f Vec3f::operator+(const Vec3f &v) const
{
  return Vec3f(m_x + v.x(), m_y + v.y(), m_z + v.z());
}

Vec3f Vec3f::operator-(const Vec3f &v) const
{
  return Vec3f(m_x - v.x(), m_y - v.y(), m_z - v.z());
}

Vec3f Vec3f::operator-(const float &f) const
{
  return Vec3f(m_x - f, m_y - f, m_z - f);
}


Vec3f Vec3f::operator+=(const Vec3f &v)
{
  m_x += v.x();
  m_y += v.y();
  m_z += v.z();
  return *this;
}

Vec3f Vec3f::operator-=(const Vec3f &v)
{
  m_x -= v.x();
  m_y -= v.y();
  m_z -= v.z();
  return *this;
}

Vec3f Vec3f::operator*=(const float &f)
{
  m_x *= f;
  m_y *= f;
  m_z *= f;
  return *this;
}

Vec3f Vec3f::operator-() const
{
  return Vec3f(- m_x, - m_y, - m_z);
}
