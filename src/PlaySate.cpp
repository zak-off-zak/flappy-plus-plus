#include "../include/Game.h"
#include "../include/MenuState.h"
#include "../include/PlayState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <random>

PlayState::PlayState()
    : bird(212.f, 200.f, 10, -50, sf::Texture()), background_texture(),
      background_sprite(this->background_texture), score_text(this->ui_font) {}

void PlayState::init(Game *game) {
  // Set the inital state of the game
  game->game_over = false;
  game->score = 0;
  game->poped_pipes = 0;

  // Set up ranodm number generatos for generation gap positions and sizes
  this->rng = std::mt19937(std::random_device{}());
  this->gap_position_dist = std::uniform_int_distribution<int>(200, 400);
  this->gap_size_dist = std::uniform_int_distribution<int>(300, 400);
  // Set the space between the pipes
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

  this->bird = Bird(212.f, 150.f, 10, -50, this->bird_texture);

  // Setting Up Pipes
  if (!this->pipe_texture.loadFromFile(
          "assets/kenney_physics-assets/Spritesheet/"
          "spritesheet_explosive.png")) {
    std::cerr << "Error loading pipe texture!" << std::endl;
  }

  // Generate the first 7 pipes and add them to the vector
  for (int i = 0; i < 7; i++) {
    float gap_position = this->gap_position_dist(rng);
    float gap_size = this->gap_size_dist(rng);
    pipes.push_back(Pipe(game->get_window().getSize().x + i * pipe_spacing,
                         gap_position, gap_size, 100, pipe_texture));
  }

  // Set up the score text
  if (!this->ui_font.openFromFile(
          "assets/kenney_ui-pack/Font/Kenney Future.ttf")) {
    std::cerr << "Error loading ui font!" << std::endl;
  }
  this->score_text.setFont(this->ui_font);
  this->score_text.setString("Score: " + std::to_string(game->score));
  this->score_text.setCharacterSize(40);
  this->score_text.setFillColor(sf::Color(241, 156, 183));
  // Postion the score in the top-middle part of the screen
  this->score_text.setPosition({(game->get_window().getSize().x -
                                 this->score_text.getLocalBounds().size.x) /
                                    2.f,
                                30});

  this->bird.flap();
}

void PlayState::handle_input(Game *game,
                             const std::optional<sf::Event> &event) {
  // Make the bird flap if the spacebar is hit
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    bird.flap();
  }
  // Push the menu state to the stack to switch to menu without loosing the
  // progress, when the escape key is hit
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    if (!game->game_over) {
      game->push_state(std::make_unique<MenuState>());
    }
  }
}

void PlayState::update(Game *game, float time) {
  // Update only if the player has not lost yet
  if (!game->game_over) {
    // Update the bird
    this->bird.update(20 * time);

    // Update the pipes
    if (!this->pipes.empty() && this->pipes.front().is_off_screen()) {
      // Delete the unneeded pipe
      float last_pipe_x = this->pipes.back().get_upper_bounds().position.x;
      this->pipes.erase(this->pipes.begin());
      game->poped_pipes++;

      // Generate new pipe
      float gap_position = this->gap_position_dist(rng);
      float gap_size = this->gap_size_dist(rng);
      pipes.push_back(Pipe(last_pipe_x + pipe_spacing, gap_position, gap_size,
                           100, pipe_texture));
    }

    // Update the score: check the pipe with the index = (current score - popped
    // pipes) whether it is behind the bird. If so, update the score.
    if (this->pipes[game->score - game->poped_pipes]
                .get_upper_bounds()
                .position.x +
            this->pipes[game->score - game->poped_pipes]
                .get_upper_bounds()
                .size.x <
        bird.getBounds().position.x) {
      game->score++;
      this->score_text.setString("Score: " + std::to_string(game->score));
    }

    // Update pipes
    for (Pipe &pipe : pipes) {
      pipe.update(time);
      // Check for collisions. If a collision is detexted, switch to the menu
      // state with a restart button.
      if (bird.is_collided(game->get_window(), pipe)) {
        game->game_over = true;
        game->push_state(std::make_unique<MenuState>());
        break;
      }
    }
  }
}

void PlayState::render(Game *game, sf::RenderWindow &window) {
  window.draw(background_sprite);
  bird.draw(window);
  for (Pipe &pipe : pipes) {
    pipe.draw(window);
  }
  window.draw(this->score_text);
}
