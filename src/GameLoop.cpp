#include "../include/GameLoop.h"
#include "../include/Bird.h"
#include "../include/Pipe.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <vector>

void game_loop() {
  sf::RenderWindow window(sf::VideoMode({1024, 700}), "Flappy Bird",
                          sf::Style::Close | sf::Style::Titlebar);
  sf::Texture bird_texture;
  if (!bird_texture.loadFromFile("assets/images/llama_default.png")) {
    std::cerr << "Error loading bird texture!" << std::endl;
  }

  Bird bird(212.f, 100.f, 15, -15, bird_texture);
  bird.apply_force(GRAVITY);

  sf::Texture pipe_texture;
  if (!pipe_texture.loadFromFile("assets/images/pipe2.png")) {
    std::cerr << "Error loading pipe texture!" << std::endl;
  }
  std::vector<Pipe> pipes;
  for (int i = 0; i < 3; i++) {
    pipes.push_back(Pipe(i * 300, 300, 250, 10, pipe_texture));
  }

  float time = 0;

  while (window.isOpen()) {
    time += 0.00001;
    bird.update_sprite(time);
    for (auto &pipe : pipes) {
      pipe.update(time);
    }
    bool spaceWasPressed = false;
    while (const std::optional event = window.pollEvent()) {
      bool spaceIsPressed =
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
      if (spaceIsPressed && !spaceWasPressed) {
        bird.flap(time, window);
      }
      spaceWasPressed = spaceIsPressed;
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
                               [](const Pipe &p) { return p.is_off_screen(); }),
                pipes.end());
    window.clear(sf::Color::Black);
    bird.draw(window);
    for (auto pipe : pipes) {
      pipe.draw(window);
    }
    window.display();
  }
}
