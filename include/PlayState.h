#ifndef PLAY_STATE
#define PLAY_STATE

#include "Bird.h"
#include "GameState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <random>
#include <vector>

class PlayState : public GameState {
public:
  PlayState();
  void init(Game *game) override;
  void handle_input(Game *game, const std::optional<sf::Event> &event) override;
  void update(Game *game, float time) override;
  void render(Game *game, sf::RenderWindow &window) override;

protected:
private:
  Bird bird;
  std::vector<Pipe> pipes;
  float pipe_spacing;
  std::mt19937 rng;
  std::uniform_int_distribution<int> gap_position_dist;
  std::uniform_int_distribution<int> gap_size_dist;
  sf::Texture background_texture;
  sf::Sprite background_sprite;
  sf::Texture bird_texture;
  sf::Texture pipe_texture;
  sf::Font ui_font;
  sf::Text score_text;
};

#endif // !PLAY_STATE
