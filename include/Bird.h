#ifndef BIRD
#define BIRD

#include "Physics.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Bird : public Object {
public:
  Bird(float x, float y, float mass, const sf::Texture &texture);

  void draw(sf::RenderWindow &window);
  void update_position(float time);
  void flap();

protected:
private:
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif // !BIRD
