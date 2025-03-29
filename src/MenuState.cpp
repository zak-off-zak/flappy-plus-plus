#include "../include/MenuState.h"
#include "../include/Game.h"
#include "../include/PlayState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

MenuState::MenuState(Game &game)
    : background_sprite(game.get_background_texture()),
      menu_text(game.get_ui_font()), score_text(game.get_ui_font()),
      resume_button({float(game.get_window().getSize().x - 150) / 2.f - 100,
                     float(game.get_window().getSize().y - 50) / 2.f + 100},
                    {150, 50}, sf::RectangleShape({150, 50}),
                    sf::Color(61, 186, 77),
                    sf::Text(game.get_ui_font(), "Resume"), game.get_ui_font(),
                    25, [this, &game]() { this->resume(game); }),
      restart_button(
          {float(game.get_window().getSize().x - 150) / 2.f + 100,
           float(game.get_window().getSize().y - 50) / 2.f + 100},
          {150, 50}, sf::RectangleShape({150, 50}), sf::Color(199, 57, 53),
          sf::Text(game.get_ui_font(), "Restart"), game.get_ui_font(), 25,
          [this, &game]() { this->restart(game); }) {}

void MenuState::init(Game &game) {
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

  // Setting Up the Menu-UI

  // Background Rectangle (to be used as background for text and buttons)
  this->rectangle = sf::RectangleShape(sf::Vector2f(400.f, 300.f));
  this->rectangle.setFillColor(sf::Color(91, 209, 195));
  this->rectangle.setPosition(
      {float(window_size.x - this->rectangle.getSize().x) / 2.f,
       float(window_size.y - this->rectangle.getSize().y) / 2.f});

  // Setting the titel
  // Set the appropriate title text based on the game_over variable
  if (game.game_over) {
    this->menu_text.setString("Game Over");
    this->menu_text.setCharacterSize(55);
  } else {
    this->menu_text.setString("Menu");
    this->menu_text.setCharacterSize(80);
  }
  // Position the menu text in the top-middle part of the background rectangle
  this->menu_text.setPosition({(this->rectangle.getPosition().x +
                                (this->rectangle.getLocalBounds().size.x -
                                 this->menu_text.getLocalBounds().size.x) /
                                    2.f),
                               (this->rectangle.getPosition().y)});

  // Setting the score text
  this->score_text.setString("Score: " + std::to_string(game.score));
  this->score_text.setCharacterSize(40);
  // Postion the score below the title
  this->score_text.setPosition({(this->rectangle.getPosition().x +
                                 (this->rectangle.getLocalBounds().size.x -
                                  this->score_text.getLocalBounds().size.x) /
                                     2.f),
                                (this->rectangle.getPosition().y +
                                 this->rectangle.getLocalBounds().size.y / 2.f -
                                 this->score_text.getLocalBounds().size.y)});

  // Change the position of the restart button based on the game_over state
  if (!game.game_over) {
    this->restart_button.setPosition(
        {float(window_size.x - this->restart_button.getSize().x) / 2.f + 100,
         float(window_size.y - this->restart_button.getSize().y) / 2.f + 100});
  } else {
    this->restart_button.setPosition(
        {float(window_size.x - this->restart_button.getSize().x) / 2.f,
         float(window_size.y - this->restart_button.getSize().y) / 2.f + 100});
  }
}

void MenuState::handle_input(Game &game,
                             const std::optional<sf::Event> &event) {
  // Pop the menu state when the escape key is pressed -> return to the palying
  // state
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    if (!game.game_over) {
      game.pop_state();
    }
  }
  // Handle button events
  this->resume_button.handle_event(event, game.get_window());
  this->restart_button.handle_event(event, game.get_window());
}

void MenuState::resume(Game &game) {
  // Pop the current menu state and return to the playing state, if the mouse
  // is inside the resume button
  game.pop_state();
}

void MenuState::restart(Game &game) {
  // Pop the last two states (menu and old playing state) and push a new
  // playing state, if the mouse is inside the restart button
  game.pop_state();
  game.pop_state();
  game.push_state(std::make_unique<PlayState>(game));
}

void MenuState::update(Game &game, float time) {}

void MenuState::render(Game &game, sf::RenderWindow &window) {
  // Draw all of the objects on the screen
  window.draw(background_sprite);
  window.draw(this->overlay);
  window.draw(this->rectangle);
  window.draw(this->menu_text);
  if (!game.game_over) {
    window.draw(this->resume_button);
  }
  window.draw(this->restart_button);
  window.draw(this->score_text);
}
