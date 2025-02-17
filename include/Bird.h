#ifndef BIRD
#define BIRD

#include "Physics.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Bird : public Object {
public:
  Bird(float x, float y, float mass, float falp_strength,
       const sf::Texture &texture);

  void draw(sf::RenderWindow &window);
  void update_sprite(float time);
  void flap(float &time, sf::RenderWindow &window);
  sf::FloatRect getBounds() const;

protected:
private:
  sf::Sprite sprite;
  sf::Texture texture;
  float falp_strength;
};

#endif // !BIRD
