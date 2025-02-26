#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

class CustomButton : public sf::Drawable {
public:
  CustomButton();
  CustomButton(const CustomButton &other);
  CustomButton(const sf::Vector2f &position, const sf::Vector2f &size,
               const sf::RectangleShape &shape, const sf::Color &color,
               const std::function<void()> &on_click);

  void handle_event(const std::optional<sf::Event> &event,
                    const sf::RenderWindow &window);

protected:
private:
  sf::RectangleShape shape;
  std::function<void()> on_click;

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};

#endif // !BUTTON
