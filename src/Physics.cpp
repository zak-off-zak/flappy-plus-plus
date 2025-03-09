#include "../include/Physics.h"
#include <SFML/System/Vector2.hpp>
#include <algorithm>

Object::Object(float x, float y, float mass) {
  // Set the initial values for position, mass, velocity and acceleration
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
  // Clip the velocity in order to prevent the object from accelerating
  // indefinitely
  this->velocity.x = std::min(x, 30.0f);
  this->velocity.y = std::min(y, 30.0f);
}

void Object::set_acceleration(float x, float y) {
  this->acceleration.x = x;
  this->acceleration.y = y;
}

void Object::apply_force(sf::Vector2<float> force) {
  // Apply the provided force by using the equation: F=ma (F := foce, m := mass,
  // a := acceleration)
  set_acceleration(this->acceleration.x + force.x / this->mass,
                   this->acceleration.y + force.y / this->mass);
}

void Object::update_object(float time) {
  // Calculate new velocity using the equation: v += a * t (v := velocity, a :=
  // acceleration, t := time)
  this->set_velocity(this->velocity.x += this->acceleration.x * time,
                     this->velocity.y += this->acceleration.y * time);

  // Calculate the postion by using the equation: x +=  v*t + (a*t^2)/2 (x
  // := new position, x_0 := initial position, v : = current velocity, t :=
  // time, a
  // := acceleration")
  this->set_position(
      this->position.x +=
      this->velocity.x * time + 0.5f * this->acceleration.x * time * time,
      this->position.y +=
      this->velocity.y * time + 0.5f * this->acceleration.y * time * time);
}
