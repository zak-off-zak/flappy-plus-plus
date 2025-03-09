#ifndef PHYSICS
#define PHYSICS

#include <SFML/System/Vector2.hpp>

constexpr sf::Vector2<float> GRAVITY = {0, 9.81f};

/**
 * @class Object
 * @brief Class containing essential functions for working with simple physics
 * of movement
 *
 */
class Object {
public:
  /**
   * @brief Current position of a physical obeject
   */
  sf::Vector2<float> position;
  /**
   * @brief Current velocity of a physical object
   */
  sf::Vector2<float> velocity;
  /**
   * @brief Current acceleration of a physical object
   */
  sf::Vector2<float> acceleration;
  /**
   * @brief Mass of a physical object
   */
  float mass;

  /**
   * @brief Constructor of a physical object
   *
   * @param x Initial position along the x-axis
   * @param y Initial position along the y-axis
   * @param mass Mass of a physical object
   */
  Object(float x, float y, float mass);

  /**
   * @brief Sets the position of an object
   *
   * @param x Position along the x-axis
   * @param y Position along the y-axis
   */
  void set_position(float x, float y);
  /**
   * @brief Sets the velocity of an object
   *
   * @param x Velocity along the x-axis
   * @param y Velocity along the y-axis
   */
  void set_velocity(float x, float y);
  /**
   * @brief Sets the acceleration of an object
   *
   * @param x Acceleration along the x-axis
   * @param y Acceleration along the y-axis
   */
  void set_acceleration(float x, float y);

  /**
   * @brief Applies forces to an object
   *
   * @param force A two-dimentional vector of the force
   */
  void apply_force(sf::Vector2<float> force);

  /**
   * @brief Upates the current position and velocity of an object
   * based on the time
   *
   * @param time Time to calculate the new position, velocity and acceleration
   */
  void update_object(float time);

protected:
private:
};

#endif // !PHYSICS
