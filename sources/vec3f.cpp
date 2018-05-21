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

float Vec3f::x() const { return this->m_x; }

float Vec3f::y() const { return this->m_y; }

float Vec3f::z() const { return this->m_z; }

void Vec3f::setX(float f) { this->m_x = f; }
void Vec3f::setY(float f) { this->m_y = f; }
void Vec3f::setZ(float f) { this->m_z = f; }

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
  return sqrt(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);
}

float Vec3f::norm2() const
{
  return this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z;
}

float Vec3f::dot(const Vec3f &v) const
{
  return this->m_x * v.x() + this->m_y * v.y() + this->m_z * v.z();
}

Vec3f Vec3f::operator*(const float &f) const
{
  return Vec3f(this->m_x * f, this->m_y * f, this->m_z * f);
}

Vec3f Vec3f::operator*(const Vec3f &v) const
{
  return Vec3f(m_x * v.x(), m_y * v.y(), m_z * v.z());
}

Vec3f Vec3f::operator+(const Vec3f &v) const
{
  return Vec3f(this->m_x + v.x(), this->m_y + v.y(), this->m_z + v.z());
}

Vec3f Vec3f::operator-(const Vec3f &v) const
{
  return Vec3f(this->m_x - v.x(), this->m_y - v.y(), this->m_z - v.z());
}

Vec3f Vec3f::operator-(const float &f) const
{
  return Vec3f(this->m_x - f, this->m_y - f, this->m_z - f);
}


Vec3f Vec3f::operator+=(const Vec3f &v)
{
  this->m_x += v.x();
  this->m_y += v.y();
  this->m_z += v.z();
  return *this;
}

Vec3f Vec3f::operator-=(const Vec3f &v)
{
  this->m_x -= v.x();
  this->m_y -= v.y();
  this->m_z -= v.z();
  return *this;
}

Vec3f Vec3f::operator*=(const float &f)
{
  this->m_x *= f;
  this->m_y *= f;
  this->m_z *= f;
  return *this;
}

Vec3f Vec3f::operator-() const
{
  return Vec3f(- this->m_x, - this->m_y, - this->m_z);
}
