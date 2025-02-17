#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>

#include "../include/Bird.h"
#include "../include/GameLoop.h"
#include "../include/Physics.h"

int main() {
  // Set Up
  sf::RenderWindow window(sf::VideoMode({1024, 700}), "Flappy Bird",
                          sf::Style::Close | sf::Style::Titlebar);
  sf::Texture birdTexture;
  if (!birdTexture.loadFromFile("assets/images/llama_default.png")) {
    std::cerr << "Error loading texture!" << std::endl;
  }

  Bird bird(512.f, 100.f, 15, -15, birdTexture);
  sf::CircleShape circle(50.f);
  bird.apply_force(GRAVITY);

  float time = 0;
  // Main Game Loop
  game_loop(window, bird, time);
  return 0;
}
