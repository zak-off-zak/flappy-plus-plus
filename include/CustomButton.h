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

/**
 * @class CustomButton
 * @brief A custom consisting of a shape, text and an event handler
 *
 */
class CustomButton : public sf::Drawable {
public:
  /**
   * @brief Default constructor of the custom button
   */
  CustomButton();
  /**
   * @brief Copy constructor of the custom button
   *
   * @param other [TODO:parameter]
   */
  CustomButton(const CustomButton &other);
  /**
   * @brief Constructor of the custom button
   *
   * @param position Position of the custom button
   * @param size Size of the custom button
   * @param shape Shape of the custom button
   * @param color Color of the custon button
   * @param on_click Function to be triggered when the button is pressed
   */
  CustomButton(const sf::Vector2f &position, const sf::Vector2f &size,
               const sf::RectangleShape &shape, const sf::Color &color,
               const std::function<void()> &on_click);

  /**
   * @brief Handles events to determine whether to trigger the on_click function
   *
   * @param event Event to be handeled
   * @param window Window to dertermine the position of the mouse
   */
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
