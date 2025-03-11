#include "../include/Game.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({1200, 600}), "Flappy Bird",
             sf::Style::Close | sf::Style::Titlebar) {
  // Set up the inital state of the game
  this->score = 0;
  this->poped_pipes = 0;
  this->game_over = false;
  this->load_textures();
}

void Game::push_state(std::unique_ptr<GameState> state) {
  // Init the new state and push it to the stack
  state->init(this);
  this->states.push(std::move(state));
}

void Game::pop_state() {
  // Pop the top state form the stack if it is not empty
  if (!this->states.empty()) {
    this->states.pop();
  }
}

void Game::changeState(std::unique_ptr<GameState> state) {
  // Pop the old state and push the new one
  this->pop_state();
  this->push_state(std::move(state));
}
GameState *Game::get_current_state() {
  // Return the top state if the stack is not empty, otherwise a null pointer
  return this->states.empty() ? nullptr : this->states.top().get();
}

sf::RenderWindow &Game::get_window() { return this->window; }

sf::Texture Game::get_background_texture() { return this->background_texture; }

sf::Texture Game::get_bird_texture() { return this->bird_texture; }

sf::Texture Game::get_pipe_texture() { return this->pipe_texture; }

void Game::load_textures() {

  // Load the background texture
  if (!this->background_texture.loadFromFile(
          "assets/kenney_physics-assets/PNG/Backgrounds/blue_desert.png")) {
    std::cerr << "Error loading background texture!" << std::endl;
  }

  // Load the bird texture
  if (!this->bird_texture.loadFromFile(
          "assets/kenney_physics-assets/Spritesheet/"
          "spritesheet_aliens.png")) {
    std::cerr << "Error loading bird texture!" << std::endl;
  }

  // Load the pipes texture
  if (!this->pipe_texture.loadFromFile(
          "assets/kenney_physics-assets/Spritesheet/"
          "spritesheet_explosive.png")) {
    std::cerr << "Error loading pipe texture!" << std::endl;
  }
}

void Game::run() {
  sf::Clock clock;
  // Main game loop
  while (this->window.isOpen()) {
    // Start the clock
    float time = clock.restart().asSeconds();
    // Handle events
    while (std::optional<sf::Event> event = window.pollEvent()) {
      // Check if the user wants to close the window
      if (event->is<sf::Event::Closed>()) {
        this->window.close();
      }

      // Get the current state and pass the event handling to it
      if (this->get_current_state()) {
        this->get_current_state()->handle_input(this, event);
      }
    }

    // Get the current state and update it
    if (this->get_current_state()) {
      this->get_current_state()->update(this, time);
    }

    // Clear the window, get the current state and draw it
    this->window.clear();
    if (this->get_current_state()) {
      this->get_current_state()->render(this, this->window);
    }
    // display all updates in the window
    this->window.display();
  }
}
