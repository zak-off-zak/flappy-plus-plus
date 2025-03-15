#ifndef GREETINGS_SCREEN_STATE
#define GREETINGS_SCREEN_STATE

#include "GameState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

/**
 * @class GreetingsScreenState
 * @brief Class responsible for management of the greetings screen state
 *
 */
class GreetingsScreenState : public GameState {
public:
  /**
   * @brief Greeting screen state constructor
   */
  GreetingsScreenState(Game &game);

  /**
   * @brief Initiates a new greeting screen state
   *
   * @param game Game game object containing important global informatio about
   * the game
   */
  void init(Game &game) override;
  /**
   * @brief Handles the user input while the greetings screen is being schown
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param event Event to be handeled
   */
  void handle_input(Game &game, const std::optional<sf::Event> &event) override;
  /**
   * @brief Updates the greeting screen based on the time step
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param time Time step to calculate the update to the greetings screen
   */
  void update(Game &game, float time) override;
  /**
   * @brief Renders all of the internal objects of the greetings screen state
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param window Window for the objects to be displayed in
   */
  void render(Game &game, sf::RenderWindow &window) override;

protected:
private:
  sf::Sprite background_sprite;
  sf::RectangleShape overlay;
  sf::RectangleShape rectangle;
  sf::Text welcome_text;
  sf::Text game_name_text;
  sf::Text instructions_text;
};

#endif // !GREETINGS_SCREEN_STATE
