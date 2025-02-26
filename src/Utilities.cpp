#include "../include/Utilities.h"
#include "../libs/nanosvg.h"
#include "../libs/nanosvgrast.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include <iostream>

bool check_collision(const sf::FloatRect &a, const sf::FloatRect &b) {
  return !(a.findIntersection(b) == std::nullopt);
}

sf::Texture loadSVGToTexture(const std::string &filename,
                             const unsigned int width,
                             const unsigned int height) {
  std::cout << filename << std::endl;

  std::ifstream file(filename);
  if (!file.good()) {
    std::cerr << "Error: File does not exist or cannot be accessed: "
              << filename << std::endl;
    return sf::Texture();
  }

  struct NSVGimage *image = nsvgParseFromFile(filename.c_str(), "px", 96);
  if (!image) {
    std::cerr << "Error loading SVG!" << std::endl;
    return sf::Texture();
  }

  struct NSVGrasterizer *rast = nsvgCreateRasterizer();
  unsigned char *bitmap = new unsigned char[width * height * 4];

  nsvgRasterize(rast, image, 0, 0, 1, bitmap, width, height, width * 4);

  sf::Image img({width, height}, sf::Color::Black);
  img.loadFromMemory(bitmap, width * height * 4);

  sf::Texture texture;
  if (!texture.loadFromImage(img)) {
    std::cerr << "Error creating texture!" << std::endl;
    delete[] bitmap;
    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);
    return sf::Texture();
  }

  delete[] bitmap;
  nsvgDeleteRasterizer(rast);
  nsvgDelete(image);

  return texture;
}
