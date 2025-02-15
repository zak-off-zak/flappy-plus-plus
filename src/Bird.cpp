#include "../include/Bird.h"
#include <SFML/Graphics/Sprite.hpp>

Bird::Bird(float x, float y, float mass, const sf::Texture &texture)
    : Object(x, y, mass), sprite(texture) {
  this->texture = texture;
  this->sprite.setTexture(texture);
  this->sprite.setPosition({x, y});
  // this->sprite.setScale({10, 10});
}

void Bird::draw(sf::RenderWindow &window) { window.draw(this->sprite); }

void Bird::update_position(float time) {
  this->sprite.setPosition(this->get_postion(time));
}

void Bird::flap() { this->apply_force({0, -10}); }
