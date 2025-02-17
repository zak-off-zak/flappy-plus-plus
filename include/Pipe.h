#ifndef PIPE
#define PIPE

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class Pipe {
public:
  Pipe(float inital_position, float gap_position, float gap_size, float speed,
       const sf::Texture &texture);

  void draw(sf::RenderWindow &window);
  sf::FloatRect get_upper_bounds() const;
  sf::FloatRect get_lower_bounds() const;
  bool is_off_screen() const;
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
