#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
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
   * @param other the other button that has to be copied
   */
  CustomButton(const CustomButton &other);
  /**
   * @brief Constructor of the custom button
   *
   * @param position Position of the custom button
   * @param size Size of the custom button
   * @param shape Shape of the custom button
   * @param color Color of the custon button
   * @param text Text of the button
   * @param font Font for the buttons text
   * @param on_click Function to be triggered when the button is pressed
   */
  CustomButton(const sf::Vector2f &position, const sf::Vector2f &size,
               const sf::RectangleShape &shape, const sf::Color &color,
               const sf::Text &text, const sf::Font &font,
               unsigned int font_size, const std::function<void()> &on_click);

  /**
   * @brief Handles events to determine whether to trigger the on_click function
   *
   * @param event Event to be handeled
   * @param window Window to dertermine the position of the mouse
   */
  void handle_event(const std::optional<sf::Event> &event,
                    const sf::RenderWindow &window);

  /**
   * @brief Draws the button
   *
   * @param target a reference to a SFML rendering serface (e.g. a window)
   * @param states a struct sontaining rendering options (e.g. transformations)
   */
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  /**
   * @brief Return the size of the button
   */
  sf::Vector2f getSize();

protected:
private:
  sf::RectangleShape shape;
  sf::Text text;
  sf::Font font;
  std::function<void()> on_click;
};

#endif // !BUTTON
