#include "../include/CollisionManager.h"

bool check_collision(const sf::FloatRect &a, const sf::FloatRect &b) {
  return !(a.findIntersection(b) == std::nullopt);
}
