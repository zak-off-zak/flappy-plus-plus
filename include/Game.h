#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
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
  /**
   * @brief Returns the current state from the top of the state
   *
   * @return current state of the game
   */
  GameState *get_current_state();
  /**
   * @brief Returns the window of the game
   */

  sf::RenderWindow &get_window();
  /**
   * @brief Returns the texture for the background
   */
  const sf::Texture &get_background_texture();
  /**
   * @brief Returns the texture for the bird object
   */
  sf::Texture get_bird_texture();
  /**
   * @brief Return the texture for pipes
   */
  sf::Texture get_pipe_texture();
  /**
   * @brief Return the fornt to be used for UI elemnts
   */
  const sf::Font &get_ui_font();
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
  sf::Texture background_texture;
  sf::Texture bird_texture;
  sf::Texture pipe_texture;
  sf::Font ui_font;

  void load_textures();
  void load_fonts();
};

#endif // GAME_H
