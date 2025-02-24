#ifndef GAME_STATE
#define GAME_STATE

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Game;

class GameState {
public:
  virtual ~GameState() {}

  virtual void init(Game *game) = 0;
  virtual void handle_input(Game *game,
                            const std::optional<sf::Event> &event) = 0;
  virtual void update(Game *game, float time) = 0;
  virtual void render(Game *game, sf::RenderWindow &window) = 0;

protected:
private:
};

#endif // !GAME_STATE
