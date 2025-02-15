#include "../include/Physics.h"
#include <SFML/System/Vector2.hpp>

Object::Object(float x, float y, float mass) {
  this->position.x = x;
  this->position.y = y;
  this->mass = mass;

  this->velocity.x = 0;
  this->velocity.y = 0;

  this->acceleration.x = 0;
  this->acceleration.y = 0;
}

void Object::set_position(float x, float y) {
  this->position.x = x;
  this->position.y = y;
}

void Object::set_velocity(float x, float y) {
  this->velocity.x = x;
  this->velocity.y = y;
}

void Object::set_acceleration(float x, float y) {
  this->acceleration.x = x;
  this->acceleration.y = y;
}

void Object::apply_force(sf::Vector2<float> force) {
  set_acceleration(this->acceleration.x + force.x / this->mass,
                   this->acceleration.y + force.y / this->mass);
}

sf::Vector2<float> Object::get_velocity(float time) {
  sf::Vector2<float> return_velocity;
  return_velocity.x = this->velocity.x + this->acceleration.x * time;
  return_velocity.y = this->velocity.y + this->acceleration.y * time;
  return return_velocity;
}

sf::Vector2<float> Object::get_position(float time) {
  sf::Vector2<float> return_position;
  return_position.x = this->position.x + this->velocity.x * time +
                      this->acceleration.x * (time * time) / 2;
  return_position.y = this->position.y + this->velocity.y * time +
                      this->acceleration.y * (time * time) / 2;
  return return_position;
}

void Object::update(float time) {
  this->velocity.x += this->acceleration.x * time;
  this->velocity.y += this->acceleration.y * time;

  this->position.x +=
      this->velocity.x * time + 0.5f * this->acceleration.x * time * time;
  this->position.y +=
      this->velocity.y * time + 0.5f * this->acceleration.y * time * time;
}
