#ifndef BIRD
#define BIRD

#include "Physics.h"
#include "Pipe.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

/**
 * @class Bird
 * @brief Class containing all of the information about the bird-like object
 *
 */
class Bird : public Object {
public:
  /**
   * @brief Bids constructor
   *
   * @param x birtds initial position along x-axis
   * @param y birtds initial position along y-axis
   * @param mass mass of the bird
   * @param falp_strength how strong shall the bird flap
   * @param texture texture for the birds sprite
   */
  Bird(float x, float y, float mass, float falp_strength,
       const sf::Texture &texture);

  /**
   * @brief Draws the bird
   *
   * @param window The window to draw the bird inside of
   */
  void draw(sf::RenderWindow &window);
  /**
   * @brief Updates the position of the birds sprite
   *
   * @param time The time step for that the sprite has to be updated
   */
  void update_sprite(float time);
  /**
   * @brief Make the bird flap
   *
   * @param window Window inside that the bird exists
   */
  void flap(sf::RenderWindow &window);
  /**
   * @brief Returns the bounds of the brird object
   */
  sf::FloatRect getBounds() const;
  /**
   * @brief Return whether the bird object is experiencing a collision
   *
   * @param window Window to check if the bird oject has collided with it
   * @param pipe Pipe obejct to check if the bird object has collided with it
   * @return True, if bird is experiencing a collision
   */
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
