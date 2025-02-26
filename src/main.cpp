#include "../include/Game.h"
#include "../include/MenuState.h"
#include "../include/PlayState.h"
#include <memory>

int main() {
  Game game;
  game.push_state(std::make_unique<PlayState>());
  game.push_state(std::make_unique<MenuState>());
  game.run();
  return 0;
}
