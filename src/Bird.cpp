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

void Bird::update_sprite(float time) {
  this->update(time);
  this->sprite.setPosition(this->position);
}

void Bird::flap(float &time, sf::RenderWindow &window) {
  for (int i = 0; i < 3; i++) {
    this->apply_force({0, -0.1});
    time++;
    this->update_sprite(time);
    this->draw(window);
  }
  this->apply_force({0, 0.1});
  this->update_sprite(time);
}
