#ifndef         __VEC3F_H__
#define         __VEC3F_H__

class   Vec3f
{
  private:
    float       m_x;
    float       m_y;
    float       m_z;

  public:
    Vec3f();
    Vec3f(float f);
    Vec3f(float x, float y, float z);
    ~Vec3f();

    float x() const;
    float y() const;
    float z() const;

    void setX(float f);
    void setY(float f);
    void setZ(float f);

    Vec3f &normalize();
    float norm() const;
    float norm2() const;
    float dot(const Vec3f &v) const;
    Vec3f operator*(const float &f) const;
    Vec3f operator*(const Vec3f &f) const;
    Vec3f operator+(const Vec3f &v) const;
    Vec3f operator-(const float &f) const;
    Vec3f operator-(const Vec3f &v) const;
    Vec3f operator+=(const Vec3f &v);
    Vec3f operator-=(const Vec3f &v);
    Vec3f operator*=(const float &v);
    Vec3f operator-() const;
};

#endif
