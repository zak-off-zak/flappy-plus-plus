#ifndef GREETINGS_SCREEN_STATE
#define GREETINGS_SCREEN_STATE

#include "GameState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
class GreetingsScreenState : public GameState {
public:
  GreetingsScreenState();

  void init(Game *game) override;
  void handle_input(Game *game, const std::optional<sf::Event> &event) override;
  void update(Game *game, float time) override;
  void render(Game *game, sf::RenderWindow &window) override;

protected:
private:
  sf::Texture background_texture;
  sf::Sprite background_sprite;
  sf::RectangleShape overlay;
  sf::RectangleShape rectangle;
  sf::Font ui_font;
  sf::Text welcome_text;
  sf::Text game_name_text;
  sf::Text instructions_text;
};

#endif // !GREETINGS_SCREEN_STATE
