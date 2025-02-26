#include "../include/MenuState.h"
#include "../include/Game.h"
#include "../include/PlayState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

MenuState::MenuState()
    : background_texture(), background_sprite(this->background_texture),
      menu_text(this->ui_font), resume_button_text(this->ui_font),
      restart_button_text(this->ui_font), score_text(this->ui_font) {}

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

  // TODO: Check all vectors to be declared in the same way
  this->overlay =
      sf::RectangleShape(sf::Vector2f(window_size.x, window_size.y));
  this->overlay.setFillColor(sf::Color(0, 0, 0, 150));

  // Setting Up UI

  // Background Rectangle
  this->rectangle = sf::RectangleShape(sf::Vector2f(400.f, 300.f));
  this->rectangle.setFillColor(sf::Color(91, 209, 195));
  this->rectangle.setPosition(
      {float(window_size.x - this->rectangle.getSize().x) / 2.f,
       float(window_size.y - this->rectangle.getSize().y) / 2.f});

  // Setting the header
  if (!this->ui_font.openFromFile(
          "assets/kenney_ui-pack/Font/Kenney Future.ttf")) {
    std::cerr << "Error loading ui font!" << std::endl;
  }
  this->menu_text.setFont(this->ui_font);
  this->menu_text.setString("Menu");
  this->menu_text.setCharacterSize(80);
  this->menu_text.setPosition({(this->rectangle.getPosition().x +
                                (this->rectangle.getLocalBounds().size.x -
                                 this->menu_text.getLocalBounds().size.x) /
                                    2.f),
                               (this->rectangle.getPosition().y)});

  // Setting the score text
  this->score_text.setFont(this->ui_font);
  this->score_text.setString("Score: " + std::to_string(game->score));
  this->score_text.setCharacterSize(40);
  this->score_text.setPosition({(this->rectangle.getPosition().x +
                                 (this->rectangle.getLocalBounds().size.x -
                                  this->score_text.getLocalBounds().size.x) /
                                     2.f),
                                (this->rectangle.getPosition().y +
                                 this->rectangle.getLocalBounds().size.y / 2.f -
                                 this->score_text.getLocalBounds().size.y)});

  // Creating buttons
  // this->resume_button =
  //     CustomButton({300.f, 300.f}, {100.f, 100.f}, resume_button_shape,
  //                  sf::Color::Black, [game]() { game->pop_state(); });
  //                  Resume button
  this->resume_button = sf::RectangleShape({150, 50});
  this->resume_button.setFillColor(sf::Color(61, 186, 77));
  this->resume_button.setPosition(
      {float(window_size.x - this->resume_button.getSize().x) / 2.f - 100,
       float(window_size.y - this->resume_button.getSize().y) / 2.f + 100});
  this->resume_button_text.setFont(this->ui_font);
  this->resume_button_text.setString("Resume");
  this->resume_button_text.setCharacterSize(25);
  this->resume_button_text.setPosition(
      {this->resume_button.getPosition().x +
           ((this->resume_button.getLocalBounds().size.x -
             this->resume_button_text.getLocalBounds().size.x) /
            2.f),
       this->resume_button.getPosition().y +
           this->resume_button_text.getLocalBounds().size.y / 2.f});
  //                  Restart button
  this->restart_button = sf::RectangleShape({150, 50});
  this->restart_button.setFillColor(sf::Color(199, 57, 53));
  this->restart_button.setPosition(
      {float(window_size.x - this->restart_button.getSize().x) / 2.f + 100,
       float(window_size.y - this->restart_button.getSize().y) / 2.f + 100});
  this->restart_button_text.setFont(this->ui_font);
  this->restart_button_text.setString("Restart");
  this->restart_button_text.setCharacterSize(25);
  this->restart_button_text.setPosition(
      {this->restart_button.getPosition().x +
           ((this->restart_button.getLocalBounds().size.x -
             this->restart_button_text.getLocalBounds().size.x) /
            2.f),
       this->restart_button.getPosition().y +
           this->restart_button_text.getLocalBounds().size.y / 2.f});
}

void MenuState::handle_input(Game *game,
                             const std::optional<sf::Event> &event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game->pop_state();
  }
  if (event->is<sf::Event::MouseButtonPressed>() &&
      sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    sf::Vector2f mouse_position = game->get_window().mapPixelToCoords(
        {sf::Mouse::getPosition(game->get_window())});
    if (this->resume_button.getGlobalBounds().contains(mouse_position)) {
      game->pop_state();
    }
    if (this->restart_button.getGlobalBounds().contains(mouse_position)) {
      game->pop_state();
      game->pop_state();
      game->push_state(std::make_unique<PlayState>());
    }
  }
}

void MenuState::update(Game *game, float time) {}

void MenuState::render(Game *game, sf::RenderWindow &window) {
  window.draw(background_sprite);
  window.draw(this->overlay);
  window.draw(this->rectangle);
  window.draw(this->menu_text);
  window.draw(this->resume_button);
  window.draw(this->resume_button_text);
  window.draw(this->restart_button);
  window.draw(this->restart_button_text);
  window.draw(this->score_text);
  // window.draw(this->menu_background_sprite);
}
