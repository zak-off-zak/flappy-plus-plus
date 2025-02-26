#include "../include/Game.h"
#include "../include/GreetingsScreenState.h"
#include "../include/PlayState.h"
#include <memory>

int main() {
  Game game;
  game.push_state(std::make_unique<PlayState>());
  game.push_state(std::make_unique<GreetingsScreenState>());
  game.run();
  return 0;
}
