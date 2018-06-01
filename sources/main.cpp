#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>

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

  srand(time(NULL));

  RayTracer rayTracer(800, 600, 8., 6., 20., 10);
  SimpleScene scene = SimpleScene();

  Plane  *p = new Plane(Vec3f(0, 1, 0), Vec3f(0, 5, 0), Color(255, 255, 255), 0.5, 1, false);
  scene.addPrimitive(p);

  for (int i = -1; i < 2; i += 2)
  {
    for (int j = -1; j < 2; j += 2)
    {
      for (int k = 0; k < 3; k += 2)
      {
        Sphere *s = new Sphere(Vec3f(i * 2, j * 2, 25 + k * 5), 0.5, Color(rand() % 256, rand() % 256, rand() % 256), 0.5f, 1.0f, false);
        scene.addPrimitive(s);
      }
    }
  }

  Light *l1 = new Light(Vec3f(15, 0, 40), Color(255, 255, 255));
  Light *l2 = new Light(Vec3f(0, 0, 10), Color(255, 255, 255));

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
