#include "../include/Game.h"
#include "../include/MenuState.h"
#include "../include/PlayState.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <random>

PlayState::PlayState()
    : bird(212.f, 100.f, 10, -50, sf::Texture()), background_texture(),
      background_sprite(this->background_texture) {}

void PlayState::init(Game *game) {
  this->game_over = false;
  this->rng = std::mt19937(std::random_device{}());
  this->gap_position_dist = std::uniform_int_distribution<int>(200, 400);
  this->gap_size_dist = std::uniform_int_distribution<int>(300, 400);
  this->pipe_spacing = 400;

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

  // Setting Up the Bird
  if (!this->bird_texture.loadFromFile(
          "assets/kenney_physics-assets/Spritesheet/"
          "spritesheet_aliens.png")) {
    std::cerr << "Error loading bird texture!" << std::endl;
  }

  this->bird = Bird(212.f, 100.f, 10, -50, this->bird_texture);

  // Setting Up Pipes
  if (!this->pipe_texture.loadFromFile(
          "assets/kenney_physics-assets/Spritesheet/"
          "spritesheet_explosive.png")) {
    std::cerr << "Error loading pipe texture!" << std::endl;
  }

  for (int i = 0; i < 7; i++) {
    float gap_position = this->gap_position_dist(rng);
    float gap_size = this->gap_size_dist(rng);
    pipes.push_back(Pipe(game->get_window().getSize().x + i * pipe_spacing,
                         gap_position, gap_size, 100, pipe_texture));
  }
}

void PlayState::handle_input(Game *game,
                             const std::optional<sf::Event> &event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    bird.flap(game->get_window());
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game->push_state(std::make_unique<MenuState>());
  }
}

void PlayState::update(Game *game, float time) {
  if (!game_over) {
    this->bird.update_sprite(20 * time);
    if (!this->pipes.empty() && this->pipes.front().is_off_screen()) {
      // Delete the unneeded pipe
      float last_pipe_x = this->pipes.back().get_upper_bounds().position.x;
      this->pipes.erase(this->pipes.begin());

      // Generate new pipe
      float gap_position = this->gap_position_dist(rng);
      float gap_size = this->gap_size_dist(rng);
      pipes.push_back(Pipe(last_pipe_x + pipe_spacing, gap_position, gap_size,
                           100, pipe_texture));
    }
    for (auto &pipe : pipes) {
      pipe.update(time);
      if (bird.is_collided(game->get_window(), pipe)) {

        std::cout << "Collision detected!" << std::endl;
        this->game_over = true;
        break;
      }
    }
  }
}

void PlayState::render(Game *game, sf::RenderWindow &window) {
  window.draw(background_sprite);
  bird.draw(window);
  for (auto &pipe : pipes) {
    pipe.draw(window);
  }
}
