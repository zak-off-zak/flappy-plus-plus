#include "Game.h"
#include "GreetingsScreenState.h"
#include "PlayState.h"
#include <memory>

int main() {
  // Create a new instance of the game. Start the game by pushing the PlayState
  // ot the stack. Display the greeting screen by pushing the
  // GreetingsScreenState on top of it. Run the game.
  Game game;
  game.push_state(std::make_unique<PlayState>(game));
  game.push_state(std::make_unique<GreetingsScreenState>(game));
  game.run();
  return 0;
}
