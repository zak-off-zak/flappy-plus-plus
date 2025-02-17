#include "../include/Pipe.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Pipe::Pipe(float inital_position, float gap_position, float gap_size,
           float speed, const sf::Texture &texture)
    : lower_pipe(texture), upper_pipe(texture) {
  this->lower_pipe.setTexture(texture);
  this->upper_pipe.setTexture(texture);
  this->inital_position = inital_position;
  this->gap_position = gap_position;
  this->gap_size = gap_size;
  this->speed = speed;

  sf::IntRect pipe_rect({0, 0}, {300, 700});
  this->lower_pipe.setTextureRect(pipe_rect);
  this->upper_pipe.setTextureRect(pipe_rect);

  sf::Vector2u texture_size = texture.getSize();

  // float scale_x =
  //     static_cast<float>(pipe_rect.size.x) /
  //     static_cast<float>(texture_size.x);
  // float scale_y =
  //     static_cast<float>(pipe_rect.size.y) /
  //     static_cast<float>(texture_size.y);
  //
  // this->lower_pipe.setScale({scale_x, scale_y});
  // this->upper_pipe.setScale({scale_x, -scale_y});
  this->lower_pipe.setScale({1.f, 1.f});
  this->upper_pipe.setScale({1.f, -1.f});

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
  return (this->upper_pipe.getPosition().x +
              this->upper_pipe.getGlobalBounds().size.x <
          0);
}

void Pipe::update(float time) {
  this->upper_pipe.move({-this->speed * time, 0.f});
  this->lower_pipe.move({-this->speed * time, 0.f});
}
