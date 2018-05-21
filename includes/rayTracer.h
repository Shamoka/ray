#ifndef         __RAY_TRACER_H__
#define         __RAY_TRACER_H__

#include "vec3f.h"
#include "simpleScene.h"

class RayTracer
{
  private:
    Vec3f               m_origin;
    Vec3f               m_direction;
    unsigned long       m_pixelWidth;
    unsigned long       m_pixelHeight;
    float               m_width;
    float               m_height;
    float               m_depth;
    float               m_precompWidth;
    float               m_precompHeight;
    SimpleScene         *m_scene;
    unsigned int        m_levels;

    void generateRay(unsigned long x, unsigned long y, Ray &ray) const;
    void computeColor(const Ray &ray, Color &color, unsigned int level) const;
    void updateParameters();

  public:
    RayTracer(unsigned long pixelWidth, unsigned long pixelHeight,
        float width, float height, float depth, unsigned int levels);
    ~RayTracer();
    void draw(Color *screen) const;
    void setViewer(float width, float height, const Vec3f &origin, const Vec3f &direction);
    void setResolution(unsigned long pixelWidth, unsigned long pixelHeight);
    void setScene(SimpleScene *scene);
};

#endif
