#include <cmath>
#include <iostream>

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
      computeColor(ray, color, 0, 1.0f);
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

void RayTracer::computeColor(const Ray &ray, Color &color, unsigned int level, float refract) const
{
  float                 dist;
  long                  index;
  MaterialPoint         mp;

  index = m_scene->getFirstCollision(ray, dist);
  if (index < 0)
    return;

  Primitive *primitive = m_scene->getPrimitive(index);
  primitive->computeColorNormal(ray, dist, mp);
  color = m_scene->computeColor(ray.origin() + ray.direction() * dist, mp);

  if (level < m_levels)
  {
    if (primitive->transparent())
    {
      Vec3f refracted_dir;
      getRefracted(refracted_dir, mp.normal, ray.direction(), refract, mp.refract);
      Ray refracted(ray.origin() + ray.direction() * dist, refracted_dir);
      float reflectance = computeReflectance(mp.normal, refracted.direction(), refract, mp.refract);
      Color color_refracted(0, 0, 0);
      if (refract == mp.refract)
        computeColor(refracted, color_refracted, level + 1, 1.0f);
      else
        computeColor(refracted, color_refracted, level + 1, mp.refract);
      Color color_reflected(0, 0, 0);
      Ray reflected(ray.origin() + ray.direction() * dist,
          getReflected(mp.normal, ray.direction()));
      computeColor(reflected, color_reflected, level + 1, refract);
      color = color_refracted.mean(color_reflected, (1.0 - reflectance), reflectance);
    }
    else
    {
      Ray reflected(ray.origin() + ray.direction() * dist,
          getReflected(mp.normal, ray.direction()));
      Color color_sec(0, 0, 0);
      computeColor(reflected, color_sec, level + 1, refract);
      color += color_sec * mp.reflect;
    }
  }
}

void RayTracer::updateParameters()
{
  m_precompWidth = m_width / m_pixelWidth;
  m_precompHeight = m_height / m_pixelHeight;
}

Vec3f RayTracer::getReflected(const Vec3f &normal, const Vec3f &ray) const
{
  float cosI = - (normal * ray);
  return ray + normal * 2 * cosI;
}

bool RayTracer::getRefracted(Vec3f &refracted, const Vec3f &normal, 
    const Vec3f &ray, float n1, float n2) const
{
  float n = n1 / n2;
  float cosI = fabs(normal * ray);
  float sinT2 = n * n * (1.0 - cosI * cosI);
  if (sinT2 > 1.0)
    return false;
  float cosT = sqrt(1.0 - sinT2);
  refracted = ray * n + normal * (n * cosI - cosT);
  return true;
}

float RayTracer::computeReflectance(const Vec3f &normal, const Vec3f &ray,
    float n1, float n2) const
{
  float n = n1 / n2;
  float cosI = fabs(normal * ray);
  float sinT2 = n * n * (1.0f - cosI * cosI);
  if (sinT2 > 1.0f)
    return 1.0f;
  float cosT = sqrt(1.0f - sinT2);
  float rOrth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
  float rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
  return (rOrth * rOrth + rPar * rPar) / 2.0f;
}
