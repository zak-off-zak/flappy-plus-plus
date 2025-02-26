#ifndef UTILITIES
#define UTILITIES

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
bool check_collision(const sf::FloatRect &a, const sf::FloatRect &b);
sf::Texture loadSVGToTexture(const std::string &filename,
                             const unsigned int width,
                             const unsigned int height);

#endif // !UTILITIES
