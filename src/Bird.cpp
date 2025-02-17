#include "../include/Bird.h"
#include <SFML/Graphics/Sprite.hpp>

Bird::Bird(float x, float y, float mass, float falp_strength,
           const sf::Texture &texture)
    : Object(x, y, mass), sprite(texture) {
  this->texture = texture;
  this->sprite.setTexture(texture);
  this->sprite.setPosition({x, y});
  this->falp_strength = falp_strength;
  this->sprite.setScale({0.5, 0.5});
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
