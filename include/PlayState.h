#ifndef PLAY_STATE
#define PLAY_STATE

#include "Bird.h"
#include "GameState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <random>
#include <vector>

/**
 * @class PlayState
 * @brief Class containing the information about the states of the game, when it
 * is being played by the user
 *
 */
class PlayState : public GameState {
public:
  /**
   * @brief Constructor of the playing state
   */
  PlayState(Game &game);
  /**
   * @brief Initiates a new playing state
   *
   * @param game Game game object containing important global informatio about
   * the game
   */
  void init(Game *game) override;
  /**
   * @brief Handles the user input, e.g. a pressing on the space to make
   * a bird flap
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param event Event that has to be handeled
   */
  void handle_input(Game *game, const std::optional<sf::Event> &event) override;
  /**
   * @brief Updates all object inside the playing state, e.g. the bird and all
   * of the pipes
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param time Time step to update all of the objects
   */
  void update(Game *game, float time) override;
  /**
   * @brief Renders all of the playing state objests
   *
   * @param game Game game object containing important global informatio about
   * the game
   * @param window Window for the objects to be displayed in
   */
  void render(Game *game, sf::RenderWindow &window) override;

protected:
private:
  Bird bird;
  std::vector<Pipe> pipes;
  float pipe_spacing;
  std::mt19937 rng;
  std::uniform_int_distribution<int> gap_position_dist;
  std::uniform_int_distribution<int> gap_size_dist;
  sf::Sprite background_sprite;
  sf::Texture bird_texture;
  sf::Texture pipe_texture;
  sf::Text score_text;
};

#endif // !PLAY_STATE
