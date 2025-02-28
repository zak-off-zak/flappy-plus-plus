#ifndef UTILITIES
#define UTILITIES

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
/**
 * @brief Checks whether to rectangles are colliding
 *
 * @param a First rectangle
 * @param b Second rectangle
 * @return True, if there is a collision between two rectangles
 */
bool check_collision(const sf::FloatRect &a, const sf::FloatRect &b);
#endif // !UTILITIES
