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
