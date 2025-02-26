#include "../include/MenuState.h"
#include "../include/Game.h"
#include "../include/Utilities.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

MenuState::MenuState()
    : background_texture(), background_sprite(this->background_texture),
      menu_text(this->ui_font) {}

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

  this->overlay =
      sf::RectangleShape(sf::Vector2f(window_size.x, window_size.y));
  this->overlay.setFillColor(sf::Color(0, 0, 0, 150));

  // Setting Up UI
  this->rectangle = sf::RectangleShape(sf::Vector2f(400.f, 300.f));
  rectangle.setFillColor(sf::Color(47, 215, 146));
  rectangle.setPosition(
      {float(window_size.x - this->rectangle.getSize().x) / 2.f,
       float(window_size.y - this->rectangle.getSize().y) / 2.f});

  // Setting text
  if (!this->ui_font.openFromFile(
          "assets/kenney_ui-pack/Font/Kenney Future.ttf")) {
    std::cerr << "Error loading ui font!" << std::endl;
  }
  this->menu_text.setFont(this->ui_font);
  this->menu_text.setString("Menu");
  this->menu_text.setCharacterSize(60);
  this->menu_text.setPosition(
      {float(window_size.x - this->rectangle.getSize().x) / 2.f +
           this->menu_text.getLocalBounds().size.x / 2.f,
       float(window_size.y - this->rectangle.getSize().y) / 2.f +
           this->menu_text.getLocalBounds().size.y / 2.f});

  // this->menu_background_texture =
  //     loadSVGToTexture("/Users/zak/Documents/Code/cpp-flappy-bird/assets/"
  //                      "kenney_ui-pack/Vector/Green/check_square_color.svg",
  //                      300, 300);
  // if (!this->menu_background_texture.loadFromFile(
  //         "assets/kenney_ui-pack/PNG/Green/Double/check_square_color.png"))
  //         {
  //   std::cerr << "Error loading background texture!" << std::endl;
  // }
  //
  // this->menu_background_sprite = sf::Sprite(this->menu_background_texture);
  // this->menu_background_sprite.setTexture(this->menu_background_texture);
  // this->menu_background_sprite.setScale({3, 2});
  // this->menu_background_sprite.setPosition({300, 300});
}

void MenuState::handle_input(Game *game,
                             const std::optional<sf::Event> &event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game->pop_state();
  }
}

void MenuState::update(Game *game, float time) {}

void MenuState::render(Game *game, sf::RenderWindow &window) {
  window.draw(background_sprite);
  window.draw(this->overlay);
  window.draw(this->rectangle);
  window.draw(this->menu_text);
  // window.draw(this->menu_background_sprite);
}
