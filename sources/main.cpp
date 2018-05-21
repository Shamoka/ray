#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "color.h"
#include "rayTracer.h"
#include "simpleScene.h"
#include "sphere.h"

int main(int ac, char **av)
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Ray");
  sf::Uint8 *pixels = new sf::Uint8[800 * 600 * 4];
  sf::Texture texture;
  Color colorMap[800 * 600];

  RayTracer rayTracer(800, 600, 8., 6., 40., 10);
  SimpleScene scene = SimpleScene();

  Sphere *s1 = new Sphere(Vec3f(0., 0., 60.), 2., Color(45, 168, 201));
  Sphere *s2 = new Sphere(Vec3f(1.5, 3., 60.), 1., Color(210, 40, 50));
  Sphere *s3 = new Sphere(Vec3f(-1.5, -3., 60.), 1., Color(120, 12, 128));

  scene.addPrimitive(s1);
  scene.addPrimitive(s2);
  scene.addPrimitive(s3);

  Light *l1 = new Light(Vec3f(3., 3., 50), Color(10, 10, 10));

  scene.addLight(l1);

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
  }
  return 0;
}
