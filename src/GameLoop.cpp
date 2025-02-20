#include "../include/GameLoop.h"
#include "../include/Bird.h"
#include "../include/Pipe.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>
#include <vector>

void game_loop() {
  sf::RenderWindow window(sf::VideoMode({1024, 700}), "Flappy Bird",
                          sf::Style::Close | sf::Style::Titlebar);
  sf::Texture background_texture;
  if (!background_texture.loadFromFile(
          "assets/tappyplane/PNG/background.png")) {
    std::cerr << "Error loading background texture!" << std::endl;
  }

  sf::Sprite background_sprite(background_texture);
  background_sprite.setTexture(background_texture);

  sf::Vector2u window_size = window.getSize();
  sf::FloatRect background_bounds = background_sprite.getGlobalBounds();
  background_sprite.setScale({float(window_size.x) / background_bounds.size.x,
                              float(window_size.y) / background_bounds.size.y});

  sf::Texture bird_texture;
  // if (!bird_texture.loadFromFile("assets/images/llama_default.png")) {
  if (!bird_texture.loadFromFile("assets/tappyplane/Spritesheet/planes.png")) {
    std::cerr << "Error loading bird texture!" << std::endl;
  }

  Bird bird(212.f, 100.f, 10, -15, bird_texture);
  bird.apply_force(GRAVITY);

  sf::Texture pipe_texture;
  if (!pipe_texture.loadFromFile("assets/images/pipe2.png")) {
    std::cerr << "Error loading pipe texture!" << std::endl;
  }

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> gap_heit_dist(200, 500);
  float pipe_spacing = 200;
  std::vector<Pipe> pipes;
  for (int i = 0; i < 7; i++) {
    float gap_position = gap_heit_dist(rng);
    pipes.push_back(Pipe(window.getSize().x + i * pipe_spacing, gap_position,
                         250, 0.0001, pipe_texture));
  }

  sf::Clock clock;
  while (window.isOpen()) {
    float time = clock.restart().asMicroseconds();
    bird.update_sprite(time / 50000);
    if (!pipes.empty() && pipes.front().is_off_screen()) {
      float last_pipe_x = pipes.back().get_upper_bounds().position.x;
      pipes.erase(pipes.begin());
      float gap_position = gap_heit_dist(rng);
      pipes.push_back(Pipe(last_pipe_x + pipe_spacing, gap_position, 250,
                           0.0001, pipe_texture));
    }
    for (auto &pipe : pipes) {
      pipe.update(time);
      if (bird.is_collided(window, pipe)) {

        std::cout << "Collision detected!" << std::endl;
        // exit(-1);
      }
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
    window.clear(sf::Color::Black);
    window.draw(background_sprite);
    bird.draw(window);
    for (auto &pipe : pipes) {
      pipe.draw(window);
    }
    window.display();
  }
}
