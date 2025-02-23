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
  sf::RenderWindow window(sf::VideoMode({1200, 600}), "Flappy Bird",
                          sf::Style::Close | sf::Style::Titlebar);
  // Setting Up Background
  sf::Texture background_texture;
  if (!background_texture.loadFromFile(
          "assets/kenney_physics-assets/PNG/Backgrounds/blue_desert.png")) {
    std::cerr << "Error loading background texture!" << std::endl;
  }

  sf::Sprite background_sprite(background_texture);
  background_sprite.setTexture(background_texture);

  sf::Vector2u window_size = window.getSize();
  sf::FloatRect background_bounds = background_sprite.getGlobalBounds();
  background_sprite.setScale({float(window_size.x) / background_bounds.size.x,
                              float(window_size.y) / background_bounds.size.y});

  // Setting Up the Bird
  sf::Texture bird_texture;
  if (!bird_texture.loadFromFile("assets/kenney_physics-assets/Spritesheet/"
                                 "spritesheet_aliens.png")) {
    std::cerr << "Error loading bird texture!" << std::endl;
  }

  Bird bird(212.f, 100.f, 10, -50, bird_texture);

  // Setting Up Pipes
  sf::Texture pipe_texture;
  if (!pipe_texture.loadFromFile("assets/kenney_physics-assets/Spritesheet/"
                                 "spritesheet_explosive.png")) {
    std::cerr << "Error loading pipe texture!" << std::endl;
  }

  // Generating Initial Pipes
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> gap_position_dist(200, 400);
  std::uniform_int_distribution<int> gap_size_dist(300, 400);
  float pipe_spacing = 400;
  std::vector<Pipe> pipes;
  for (int i = 0; i < 7; i++) {
    float gap_position = gap_position_dist(rng);
    float gap_size = gap_size_dist(rng);
    pipes.push_back(Pipe(window.getSize().x + i * pipe_spacing, gap_position,
                         gap_size, 100, pipe_texture));
  }

  bool breaked = false;

  sf::Clock clock;
  while (window.isOpen()) {
    float time = clock.restart().asSeconds();

    // Event handling
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

    // Update
    if (!breaked) {

      bird.update_sprite(20 * time);
      if (!pipes.empty() && pipes.front().is_off_screen()) {
        // Delete the unneeded pipe
        float last_pipe_x = pipes.back().get_upper_bounds().position.x;
        pipes.erase(pipes.begin());

        // Generate new pipe
        float gap_position = gap_position_dist(rng);
        float gap_size = gap_size_dist(rng);
        pipes.push_back(Pipe(last_pipe_x + pipe_spacing, gap_position, gap_size,
                             100, pipe_texture));
      }
      for (auto &pipe : pipes) {
        pipe.update(time);
        if (bird.is_collided(window, pipe)) {

          std::cout << "Collision detected!" << std::endl;
          breaked = true;
          break;
        }
      }
    }

    // Draw & Display
    window.clear(sf::Color::Black);
    window.draw(background_sprite);
    bird.draw(window);
    for (auto &pipe : pipes) {
      pipe.draw(window);
    }
    window.display();
  }
}
