#include "../include/GreetingsScreenState.h"
#include "../include/Game.h"
#include "../include/MenuState.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <memory>

GreetingsScreenState::GreetingsScreenState()
    : background_sprite(this->background_texture), welcome_text(this->ui_font),
      game_name_text(this->ui_font), instructions_text(this->ui_font) {}

void GreetingsScreenState::init(Game *game) {
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

  // TODO: Check all vectors to be declared in the same way
  this->overlay =
      sf::RectangleShape(sf::Vector2f(window_size.x, window_size.y));
  this->overlay.setFillColor(sf::Color(0, 0, 0, 150));

  this->rectangle = sf::RectangleShape(sf::Vector2f(700.f, 250.f));
  this->rectangle.setFillColor(sf::Color(91, 209, 195));
  this->rectangle.setPosition(
      {float(window_size.x - this->rectangle.getSize().x) / 2.f,
       float(window_size.y - this->rectangle.getSize().y) / 2.f});

  // Setting the header
  if (!this->ui_font.openFromFile(
          "assets/kenney_ui-pack/Font/Kenney Future.ttf")) {
    std::cerr << "Error loading ui font!" << std::endl;
  }
  this->welcome_text.setFont(this->ui_font);
  this->welcome_text.setString("Welcome to");
  this->welcome_text.setCharacterSize(30);
  this->welcome_text.setPosition(
      {(this->rectangle.getPosition().x +
        (this->rectangle.getLocalBounds().size.x -
         this->welcome_text.getLocalBounds().size.x) /
            2.f),
       (this->rectangle.getPosition().y) + 30});

  this->game_name_text.setFont(this->ui_font);
  this->game_name_text.setString("Flappy-Plus-Plus");
  this->game_name_text.setCharacterSize(50);
  this->game_name_text.setFillColor(sf::Color(255, 204, 1));
  this->game_name_text.setStyle(sf::Text::Bold);
  this->game_name_text.setPosition(
      {(this->rectangle.getPosition().x +
        (this->rectangle.getLocalBounds().size.x -
         this->game_name_text.getLocalBounds().size.x) /
            2.f),
       (this->welcome_text.getPosition().y + 50)});

  this->instructions_text.setFont(this->ui_font);
  this->instructions_text.setString(
      "Press Space to start\nPress Escape to open the menu");
  this->instructions_text.setCharacterSize(20);
  this->instructions_text.setPosition(
      {(this->rectangle.getPosition().x +
        (this->rectangle.getLocalBounds().size.x -
         this->instructions_text.getLocalBounds().size.x) /
            2.f),
       (this->game_name_text.getPosition().y + 100)});
}

void GreetingsScreenState::handle_input(Game *game,
                                        const std::optional<sf::Event> &event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    game->pop_state();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game->changeState(std::make_unique<MenuState>());
  }
}

void GreetingsScreenState::update(Game *game, float time) {}

void GreetingsScreenState::render(Game *game, sf::RenderWindow &window) {
  window.draw(background_sprite);
  window.draw(this->overlay);
  window.draw(this->rectangle);
  window.draw(this->welcome_text);
  window.draw(this->game_name_text);
  window.draw(this->instructions_text);
}
