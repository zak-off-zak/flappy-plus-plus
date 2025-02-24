#ifndef MENU_STATE
#define MENU_STATE

#include "GameState.h"
#include <SFML/Graphics/Sprite.hpp>
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
};

#endif // !MENU_STATE
