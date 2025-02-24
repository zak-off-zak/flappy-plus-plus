#include "../include/Game.h"
#include <iostream>

void Game::push_state(std::unique_ptr<GameState> state) {
  std::cout << "1" << std::endl;
  state->init(this);
  this->states.push(std::move(state));
  std::cout << "2" << std::endl;
}

void Game::pop_state() {
  if (!this->states.empty()) {
    this->states.pop();
  }
}

void Game::changeState(std::unique_ptr<GameState> state) {
  this->pop_state();
  this->push_state(std::move(state));
}
GameState *Game::get_current_state() {
  return this->states.empty() ? nullptr : this->states.top().get();
}

sf::RenderWindow &Game::get_window() { return this->window; }

void Game::run() {
  sf::Clock clock;
  while (this->window.isOpen()) {
    float time = clock.restart().asSeconds();
    while (std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        this->window.close();
      }

      if (this->get_current_state())
        this->get_current_state()->handle_input(this, event);
    }

    if (this->get_current_state())
      this->get_current_state()->update(this, time);

    this->window.clear();
    if (this->get_current_state())
      this->get_current_state()->render(this, this->window);
    this->window.display();
  }
}
