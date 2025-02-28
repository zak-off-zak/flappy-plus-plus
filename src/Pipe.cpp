#include "../include/Pipe.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Pipe::Pipe(float inital_position, float gap_position, float gap_size,
           float speed, const sf::Texture &texture)
    : lower_pipe(texture), upper_pipe(texture) {
  // Set all of the attributes
  this->lower_pipe.setTexture(texture);
  this->lower_pipe.setTextureRect(sf::IntRect({710, 510}, {70, 220}));
  this->upper_pipe.setTexture(texture);
  this->upper_pipe.setTextureRect(sf::IntRect({710, 510}, {70, 220}));
  this->inital_position = inital_position;
  this->gap_position = gap_position;
  this->gap_size = gap_size;
  this->speed = speed;

  this->lower_pipe.setScale({1.2f, 2.f});
  // Flip the upper pipe to make it easier to work with is position
  this->upper_pipe.setScale({1.2f, -2.f});

  // Set the position op the lower and upper pipes
  this->upper_pipe.setPosition({inital_position, gap_position});
  this->lower_pipe.setPosition({inital_position, gap_position + gap_size});
}

void Pipe::draw(sf::RenderWindow &window) {
  window.draw(this->lower_pipe);
  window.draw(this->upper_pipe);
}

sf::FloatRect Pipe::get_upper_bounds() const {
  return this->upper_pipe.getGlobalBounds();
}

sf::FloatRect Pipe::get_lower_bounds() const {
  return this->lower_pipe.getGlobalBounds();
}

bool Pipe::is_off_screen() const {
  // Check if the pipe steel can be seen on the screen
  return (this->upper_pipe.getPosition().x +
              this->upper_pipe.getGlobalBounds().size.x <
          0);
}

void Pipe::update(float time) {
  // Move pipes to the right with a specific speed
  this->upper_pipe.move({-this->speed * time, 0.f});
  this->lower_pipe.move({-this->speed * time, 0.f});
}
