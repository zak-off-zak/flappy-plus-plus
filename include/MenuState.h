#ifndef MENU_STATE
#define MENU_STATE

#include "CustomButton.h"
#include "GameState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

class MenuState : public GameState {
public:
  MenuState();

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
  sf::Text menu_text;
  sf::RectangleShape resume_button;
  sf::Text resume_button_text;
  sf::RectangleShape restart_button;
  sf::Text restart_button_text;
  sf::Text score_text;
  // CustomButton resume_button;
};

#endif // !MENU_STATE
