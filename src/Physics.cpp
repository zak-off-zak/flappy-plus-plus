#include "../include/Physics.h"

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

void Object::apply_force(Vector2D force) {
  set_acceleration(force.x / this->mass, force.y / this->mass);
}

Vector2D Object::get_velocity(float time) {
  Vector2D return_velocity;
  return_velocity.x = this->velocity.x + this->acceleration.x * time;
  return_velocity.y = this->velocity.y + this->acceleration.y * time;
  return return_velocity;
}

Vector2D Object::get_postion(float time) {
  Vector2D return_position;
  return_position.x = this->position.x + this->velocity.x * time +
                      this->acceleration.x * (time * time) / 2;
  return_position.y = this->position.y + this->velocity.y * time +
                      this->acceleration.y * (time * time) / 2;
  return return_position;
}
