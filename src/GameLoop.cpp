#include "../include/GameLoop.h"
#include "../include/Game.h"
#include "../include/PlayState.h"
#include <memory>

void game_loop() {
  Game game;
  game.push_state(std::make_unique<PlayState>());
  game.run();
}
