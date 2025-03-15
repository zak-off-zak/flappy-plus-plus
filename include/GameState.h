#ifndef GAME_STATE
#define GAME_STATE

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Game;

/**
 * @class GameState
 * @brief Class providing the interface for the states managed by the game
 *
 */
class GameState {
public:
  /**
   * @brief Destructor of the state
   */
  virtual ~GameState() {}

  /**
   * @brief Initiates new state
   *
   * @param game Game game object containing important global informatio about
   * the game
   */
  virtual void init(Game &game) = 0;
  /**
   * @brief Handles the user input based on the state
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param event Event that has to be handeled
   */
  virtual void handle_input(Game &game,
                            const std::optional<sf::Event> &event) = 0;
  /**
   * @brief Progresses the state forward
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param time The time step used to calculate the new state
   */
  virtual void update(Game &game, float time) = 0;
  /**
   * @brief Renders the state objects
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param window Window for objects to be rendered in
   */
  virtual void render(Game &game, sf::RenderWindow &window) = 0;

protected:
private:
};

#endif // !GAME_STATE
