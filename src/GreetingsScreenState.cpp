#include "../include/GreetingsScreenState.h"
#include "../include/Game.h"
#include "../include/MenuState.h"
#include <SFML/Graphics/Color.hpp>
#include <memory>

GreetingsScreenState::GreetingsScreenState(Game &game)
    : background_sprite(game.get_background_texture()),
      welcome_text(game.get_ui_font()), game_name_text(game.get_ui_font()),
      instructions_text(game.get_ui_font()) {}

void GreetingsScreenState::init(Game &game) {
  // Setting Up Background

  sf::Vector2u window_size = game.get_window().getSize();
  sf::FloatRect background_bounds = this->background_sprite.getGlobalBounds();
  this->background_sprite.setScale(
      {float(window_size.x) / background_bounds.size.x,
       float(window_size.y) / background_bounds.size.y});

  // TODO: Check all vectors to be declared in the same way

  // Init an overlay to make background appear a bit darker
  this->overlay =
      sf::RectangleShape(sf::Vector2f(window_size.x, window_size.y));
  this->overlay.setFillColor(sf::Color(0, 0, 0, 150));

  // Set up a rectangle as a base for writing text on it
  this->rectangle = sf::RectangleShape(sf::Vector2f(700.f, 250.f));
  this->rectangle.setFillColor(sf::Color(91, 209, 195));
  // Postion the rectangle in the middle of the screen
  this->rectangle.setPosition(
      {float(window_size.x - this->rectangle.getSize().x) / 2.f,
       float(window_size.y - this->rectangle.getSize().y) / 2.f});

  // Setting the titel
  this->welcome_text.setString("Welcome to");
  this->welcome_text.setCharacterSize(30);
  // Postion the welcome text in the top-middle part of the background rectangle
  this->welcome_text.setPosition(
      {(this->rectangle.getPosition().x +
        (this->rectangle.getLocalBounds().size.x -
         this->welcome_text.getLocalBounds().size.x) /
            2.f),
       (this->rectangle.getPosition().y) + 30});

  // Set up a banner with the name of the game
  this->game_name_text.setString("Flappy-Plus-Plus");
  this->game_name_text.setCharacterSize(50);
  this->game_name_text.setFillColor(sf::Color(255, 204, 1));
  this->game_name_text.setStyle(sf::Text::Bold);
  // Position it below the welcome text
  this->game_name_text.setPosition(
      {(this->rectangle.getPosition().x +
        (this->rectangle.getLocalBounds().size.x -
         this->game_name_text.getLocalBounds().size.x) /
            2.f),
       (this->welcome_text.getPosition().y + 50)});

  // Set up a text with instruction to the player
  this->instructions_text.setString(
      "Press Space to start\nPress Escape to open the menu");
  this->instructions_text.setCharacterSize(20);
  // Postion the instructions below the game name banner
  this->instructions_text.setPosition(
      {(this->rectangle.getPosition().x +
        (this->rectangle.getLocalBounds().size.x -
         this->instructions_text.getLocalBounds().size.x) /
            2.f),
       (this->game_name_text.getPosition().y + 100)});
}

void GreetingsScreenState::handle_input(Game &game,
                                        const std::optional<sf::Event> &event) {
  // Start playing the game by popping the top GreetingsScreenState
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    game.pop_state();
  }
  // Switch to the menu by changing to the MenuState
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game.changeState(std::make_unique<MenuState>(game));
  }
}

void GreetingsScreenState::update(Game &game, float time) {}

void GreetingsScreenState::render(Game &game, sf::RenderWindow &window) {
  // Draw all of the objects on the screen
  window.draw(this->background_sprite);
  window.draw(this->overlay);
  window.draw(this->rectangle);
  window.draw(this->welcome_text);
  window.draw(this->game_name_text);
  window.draw(this->instructions_text);
}
