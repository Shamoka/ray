#ifndef         __COLOR_H__
#define         __COLOR_H__

#include <vector>

class           Color
{
  private:
    float       m_r;
    float       m_g;
    float       m_b;

  public:
    Color();
    Color(float r, float g, float b);
    ~Color();

    float r() const;
    float g() const;
    float b() const;

    void setR(float r);
    void setG(float r);
    void setB(float r);

    Color operator*(const float &f) const;
    Color operator*(const Color &c) const;
    Color operator+=(const Color &c);
    Color mean(const Color &c, float c1, float c2);
};

#endif
