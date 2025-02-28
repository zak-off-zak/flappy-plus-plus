#ifndef PIPE
#define PIPE

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

/**
 * @class Pipe
 * @brief Class containing all of the information about the pipe object
 *
 */
class Pipe {
public:
  /**
   * @brief Constructor of the pipe object
   *
   * @param inital_position Initial poisition of the pipe
   * @param gap_position Position of the gap inside of the pipe
   * @param gap_size The vertical size of the gap
   * @param speed Spped of the pipe
   * @param texture Texture for the pipe object
   */
  Pipe(float inital_position, float gap_position, float gap_size, float speed,
       const sf::Texture &texture);

  /**
   * @brief Draws the pipe object
   *
   * @param window Window in wich the pipe object has to be drawn
   */
  void draw(sf::RenderWindow &window);
  /**
   * @brief Return the bounds of the upper part pipe
   */
  sf::FloatRect get_upper_bounds() const;
  /**
   * @brief Return the bounds of the lower part of the pipe
   */
  sf::FloatRect get_lower_bounds() const;
  /**
   * @brief Dertermines whether the pipe is off screen
   *
   * @return True, if the pipe can not be seen on the screen
   */
  bool is_off_screen() const;
  /**
   * @brief Updates the pipes position based on the time step
   *
   * @param time Current time step
   */
  void update(float time);

protected:
private:
  sf::Sprite lower_pipe;
  sf::Sprite upper_pipe;
  float inital_position;
  float gap_position;
  float gap_size;
  float speed;
};

#endif // !PIPE
