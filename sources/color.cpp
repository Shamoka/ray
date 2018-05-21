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

Color Color::operator*(const float &f) const
{
  return Color(m_r * f, m_g * f, m_b * f);
}

Color Color::operator*(const Color &c) const
{
  return Color(m_r * c.r(), m_g * c.g(), m_b * c.b());
}

Color Color::operator+=(const Color &c)
{
  m_r += c.r();
  m_g += c.g();
  m_b += c.b();
  return *this;
}
