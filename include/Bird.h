#ifndef BIRD
#define BIRD

#include "Physics.h"
#include "Pipe.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Bird : public Object {
public:
  Bird(float x, float y, float mass, float falp_strength,
       const sf::Texture &texture);

  void draw(sf::RenderWindow &window);
  void update_sprite(float time);
  void flap(sf::RenderWindow &window);
  sf::FloatRect getBounds() const;
  bool is_collided(sf::RenderWindow &window, Pipe &pipe);

protected:
private:
  sf::Sprite sprite;
  sf::Texture texture;
  float falp_strength;

  bool collided_with_screen_borders(sf::RenderWindow &window);
  bool collided_with_pipe(Pipe &pipe);
};

#endif // !BIRD
