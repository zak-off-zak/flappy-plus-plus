#include "../include/MenuState.h"
#include "../include/Game.h"
#include <iostream>

MenuState::MenuState()
    : background_texture(), background_sprite(this->background_texture) {}

void MenuState::init(Game *game) {
  // Setting Up Background
  if (!this->background_texture.loadFromFile(
          "assets/kenney_physics-assets/PNG/Backgrounds/blue_desert.png")) {
    std::cerr << "Error loading background texture!" << std::endl;
  }

  this->background_sprite = sf::Sprite(this->background_texture);
  this->background_sprite.setTexture(this->background_texture);

  sf::Vector2u window_size = game->get_window().getSize();
  sf::FloatRect background_bounds = this->background_sprite.getGlobalBounds();
  this->background_sprite.setScale(
      {float(window_size.x) / background_bounds.size.x,
       float(window_size.y) / background_bounds.size.y});
}

void MenuState::handle_input(Game *game,
                             const std::optional<sf::Event> &event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game->pop_state();
  }
}

void MenuState::update(Game *game, float time) {}

void MenuState::render(Game *game, sf::RenderWindow &window) {
  window.clear(sf::Color::Black);
  window.draw(background_sprite);
}
