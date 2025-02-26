#include "../include/Utilities.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

bool check_collision(const sf::FloatRect &a, const sf::FloatRect &b) {
  return !(a.findIntersection(b) == std::nullopt);
}
