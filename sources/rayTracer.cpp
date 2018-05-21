#include <math.h>

#include "rayTracer.h"

RayTracer::RayTracer(unsigned long pixelWidth, unsigned long pixelHeight,
    float width, float height, float depth, unsigned int levels) :
  m_origin(0.f), m_direction(0.f, 0.f, 1), m_pixelWidth(pixelWidth), m_pixelHeight(pixelHeight),
  m_width(width), m_height(height), m_depth(depth), m_levels(levels)
{
  updateParameters();
}

RayTracer::~RayTracer()
{}

void RayTracer::generateRay(unsigned long x, unsigned long y, Ray &ray) const
{
  ray.direction().setX(m_precompWidth * (x - m_pixelWidth / 2.f));
  ray.direction().setY(m_precompHeight * (y - m_pixelHeight / 2.f));
  ray.direction().setZ(m_depth);
  ray.direction() *= 1. / ray.direction().norm();
}

void RayTracer::draw(Color *screen) const
{
  Ray ray(m_origin, m_direction);

  for (unsigned long j = 0; j < m_pixelHeight; ++j)
  {
    for (unsigned long i = 0; i < m_pixelWidth; ++i)
    {
      generateRay(i, j, ray);
      Color color(0, 0, 0);
      computeColor(ray, color, 0);
      screen[j * m_pixelWidth + i] = color;
    }
  }
}

void RayTracer::setScene(SimpleScene *scene) { m_scene = scene; }

void RayTracer::setViewer(float width, float height, 
    const Vec3f &origin, const Vec3f &direction)
{
  m_width = width;
  m_height = height;
  m_origin = origin;
  m_direction = direction;
  updateParameters();
}

void RayTracer::computeColor(const Ray &ray, Color &color, unsigned int level) const
{
  float                 dist;
  long                  index;
  MaterialPoint         mp;

  index = m_scene->getFirstCollision(ray, dist);
  if (index < 0)
    return;

  Primitive *primitive = m_scene->getPrimitive(index);
  primitive->computeColorNormal(ray, dist, mp);
  color = mp.color;

  if (level < m_levels)
  {
    Ray ray_sec(ray.origin() + ray.direction() * dist,
        ray.direction() - mp.normal * 2 * (ray.direction().dot(mp.normal)));
    ray_sec.direction() *= 1. / ray_sec.direction().norm();
    Color color_sec(0, 0, 0);
    computeColor(ray_sec, color_sec, level + 1);
    color += color_sec * mp.reflect;
  }
}

void RayTracer::updateParameters()
{
  m_precompWidth = m_width / m_pixelWidth;
  m_precompHeight = m_height / m_pixelHeight;
}
