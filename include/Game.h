#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

class Game {
public:
  Game()
      : window(sf::VideoMode({1200, 600}), "Flappy Bird",
               sf::Style::Close | sf::Style::Titlebar) {}

  void push_state(std::unique_ptr<GameState> state);
  void pop_state();
  void changeState(std::unique_ptr<GameState> state);
  GameState *get_current_state();
  sf::RenderWindow &get_window();
  void run();

protected:
private:
  sf::RenderWindow window;
  std::stack<std::unique_ptr<GameState>> states;
};

#endif // GAME_H
