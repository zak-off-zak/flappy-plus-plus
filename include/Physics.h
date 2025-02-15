#ifndef PHYSICS
#define PHYSICS

#include <SFML/System/Vector2.hpp>

constexpr sf::Vector2<float> GRAVITY = {0, 9.81f};

class Object {
public:
  sf::Vector2<float> position;
  sf::Vector2<float> velocity;
  sf::Vector2<float> acceleration;
  float mass;

  Object(float x, float y, float mass);

  void set_position(float x, float y);
  void set_velocity(float x, float y);
  void set_acceleration(float x, float y);

  void apply_force(sf::Vector2<float> force);

  sf::Vector2<float> get_velocity(float time);
  sf::Vector2<float> get_postion(float time);

protected:
private:
};

#endif // !PHYSICS
