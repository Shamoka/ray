#ifndef         __RAY_H__
#define         __RAY_H__

#include "vec3f.h"

class           Ray
{
  private:
    Vec3f       m_origin;
    Vec3f       m_direction;

  public:
    Ray(const Vec3f &origin, const Vec3f &direction);
    ~Ray();

    const Vec3f &origin() const;
    Vec3f &origin();
    const Vec3f &direction() const;
    Vec3f &direction();
};

#endif
