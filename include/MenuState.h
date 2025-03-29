#ifndef MENU_STATE
#define MENU_STATE

#include "Button.h"
#include "GameState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

/**
 * @class MenuState
 * @brief State that handles all of the processes related to the menu
 *
 */
class MenuState : public GameState {
public:
  /**
   * @brief Menu state constructor
   */
  MenuState(Game &game);

  /**
   * @brief Initiates new menu state
   *
   * @param game Game game object containing important global informatio about
   * the game
   */
  void init(Game &game) override;
  /**
   * @brief Handles all of the user input regarding the menu
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param event Event that has to be triggered
   */
  void handle_input(Game &game, const std::optional<sf::Event> &event) override;
  /**
   * @brief Updates the internal state of the the menu
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param time Time step to calculate the new state of the menu
   */
  void update(Game &game, float time) override;
  /**
   * @brief Renders all of the internal objects of the menu state
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
  sf::Text menu_text;
  sf::Text score_text;
  Button resume_button;
  Button restart_button;

  void resume(Game &game);
  void restart(Game &game);
};

#endif // !MENU_STATE
