#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

/**
 * @class Game
 * @brief Class managing all of important inforamtion about game states and
 * transitions between them.
 *
 */
class Game {
public:
  /**
   * @brief Tells whether the collition has been detected
   */
  bool game_over;
  /**
   * @brief Score of the player
   */
  long long score;
  /**
   * @brief Number of pipes that has been poped for the pipes vector due to them
   * being not seen on the screen (they are too far left)
   */
  long long poped_pipes;

  /**
   * @brief Constructor of the game class
   */
  Game();

  /**
   * @brief Pushes a new state to the top of the stack
   *
   * @param state State to be pushed to the top of the stack
   */
  void push_state(std::unique_ptr<GameState> state);
  /**
   * @brief Pops a state from the top of the stack
   */
  void pop_state();
  /**
   * @brief Popes the most recent state form the top of the stack and pushes a
   * new one
   *
   * @param state State to be pushed to the top
   */
  void changeState(std::unique_ptr<GameState> state);
  // TODO:: Rename to peek?
  /**
   * @brief Returns the current state from the top of the state
   *
   * @return [TODO:return]
   */
  GameState *get_current_state();
  /**
   * @brief Returns the window of the game
   */
  sf::RenderWindow &get_window();
  /**
   * @brief Runs the game by taking a state form the top of the stack,
   * initializing it and running the handle_input(), update() and render()
   * methods of that state
   */
  void run();

protected:
private:
  sf::RenderWindow window;
  std::stack<std::unique_ptr<GameState>> states;
};

#endif // GAME_H
