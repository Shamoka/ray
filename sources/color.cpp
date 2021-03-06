#include <cmath>

#include "color.h"

Color::Color(float r, float g, float b) :
  m_r(r), m_g(g), m_b(b)
{}

Color::Color() :
  m_r(0), m_g(0), m_b(0)
{}

Color::~Color()
{}

float Color::r() const { return this->m_r; }

float Color::g() const { return this->m_g; }

float Color::b() const { return this->m_b; }

void Color::setR(float r)
{
  m_r = r;
}

void Color::setG(float g)
{
  m_g = g;
}

void Color::setB(float b)
{
  m_b = b;
}

Color Color::operator*(const float &f) const
{
  return Color(fmin(m_r * f, 255), fmin(m_g * f, 255), fmin(m_b * f, 255));
}

Color Color::operator*(const Color &c) const
{
  return Color(fmin(m_r * c.r(), 255), fmin(m_g * c.g(), 255), fmin(m_b * c.b(), 255));
}

Color Color::operator+=(const Color &c)
{
  m_r = fmin(m_r + c.r(), 255);
  m_g = fmin(m_g + c.g(), 255);
  m_b = fmin(m_b + c.b(), 255);
  return *this;
}

Color Color::mean(const Color &c, float c1, float c2)
{
  return Color((m_r * c1 + c.r() * c2) / (c1 + c2),
      (m_g * c1 + c.g() * c2) / (c1 + c2),
      (m_b * c1 + c.b() * c2) / (c1 + c2));
}
