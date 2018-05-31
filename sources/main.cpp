#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <thread>

#include "color.h"
#include "rayTracer.h"
#include "simpleScene.h"
#include "sphere.h"
#include "plane.h"
#include "cylindre.h"

int main(int ac, char **av)
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Ray");
  sf::Uint8 *pixels = new sf::Uint8[800 * 600 * 4];
  sf::Texture texture;
  Color colorMap[800 * 600];

  RayTracer rayTracer(800, 600, 8., 6., 20., 10);
  SimpleScene scene = SimpleScene();

  Sphere *s1 = new Sphere(Vec3f(0, 3, 40), 1., Color(0, 0, 0), 1.4f, true);
  Sphere *s2 = new Sphere(Vec3f(1, 3, 60), 1., Color(210, 40, 50), 1, false);
  Sphere *s3 = new Sphere(Vec3f(-1, 4, 60), 1., Color(120, 12, 128), 1, false);
  Plane  *p1 = new Plane(Vec3f(0, 1, 0), Vec3f(0, 5, 0), Color(255, 255, 255), 1, false);
  Cylindre *c1 = new Cylindre(Vec3f(4, 3, 50), Vec3f(1, 0, -1), 5, 1, Color(29, 123, 122), 1.3, false);

  scene.addPrimitive(s1);
  scene.addPrimitive(s2);
  scene.addPrimitive(s3);
  scene.addPrimitive(p1);
  scene.addPrimitive(c1);

  Light *l1 = new Light(Vec3f(15, 0, 40), Color(255, 255, 255));
  Light *l2 = new Light(Vec3f(0, 4, 30), Color(255, 255, 255));

  scene.addLight(l1);
  scene.addLight(l2);

  rayTracer.setScene(&scene);

  rayTracer.draw(colorMap);

  texture.create(800, 600);
  for (int i = 0; i < 800 * 600 * 4; i += 4)
  {
    pixels[i] = colorMap[i / 4].r();
    pixels[i + 1] = colorMap[i / 4].g();
    pixels[i + 2] = colorMap[i / 4].b();
    pixels[i + 3] = 128;
  }
  texture.update(pixels);
  sf::Sprite sprite(texture);
  window.draw(sprite);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 0;
}
