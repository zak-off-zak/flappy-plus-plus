#include "../include/Bird.h"
#include "../include/Utilities.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

Bird::Bird(float x, float y, float mass, float falp_strength,
           const sf::Texture &texture)
    : Object(x, y, mass), sprite(texture) {
  this->texture = texture;
  this->sprite.setTexture(texture);
  this->sprite.setTextureRect(sf::IntRect({70, 140}, {70, 70}));
  this->sprite.setPosition({x, y});
  this->falp_strength = falp_strength;
  this->apply_force(this->mass * GRAVITY);
}

void Bird::draw(sf::RenderWindow &window) { window.draw(this->sprite); }

void Bird::update_sprite(float time) {
  this->update(time);
  this->sprite.setPosition(this->position);
}

void Bird::flap(float &time, sf::RenderWindow &window) {
  this->set_velocity(this->velocity.x, this->falp_strength);
}

sf::FloatRect Bird::getBounds() const { return this->sprite.getGlobalBounds(); }

bool Bird::collided_with_screen_borders(sf::RenderWindow &window) {
  if (this->getBounds().position.x < 0 ||
      this->getBounds().position.x + this->getBounds().size.x >
          window.getSize().x) {
    return true;
  }
  if (this->getBounds().position.y < 0 ||
      this->getBounds().position.y + this->getBounds().size.y >
          window.getSize().y) {
    return true;
  }
  return false;
}

bool Bird::collided_with_pipe(Pipe &pipe) {
  if (check_collision(this->getBounds(), pipe.get_upper_bounds()) ||
      check_collision(this->getBounds(), pipe.get_lower_bounds())) {
    return true;
  }
  return false;
}

bool Bird::is_collided(sf::RenderWindow &window, Pipe &pipe) {
  return this->collided_with_pipe(pipe) ||
         this->collided_with_screen_borders(window);
}
