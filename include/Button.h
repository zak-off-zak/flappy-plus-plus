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
 * @class Button
 * @brief A custom consisting of a shape, text and an event handler
 *
 */
class Button : public sf::Drawable {
public:
  /**
   * @brief Default constructor of the custom button
   */
  Button();
  /**
   * @brief Copy constructor of the custom button
   *
   * @param other the other button that has to be copied
   */
  Button(const Button &other);
  /**
   * @brief Constructor of the custom button
   *
   * @param position Position of the custom button
   * @param shape Shape of the custom button
   * @param color Color of the custon button
   * @param text Text of the button
   * @param font Font for the buttons text
   * @param on_click Function to be triggered when the button is pressed
   */
  Button(const sf::Vector2f &position, const sf::RectangleShape &shape,
         const sf::Color &color, const sf::Text &text, const sf::Font &font,
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

  /**
   * @brief Setter for the positon of the bustton
   *
   * @param new_position The new position of the button
   */
  void setPosition(sf::Vector2f new_position);

protected:
private:
  sf::RectangleShape shape;
  sf::Text text;
  sf::Font font;
  std::function<void()> on_click;

  void place_text();
};

#endif // !BUTTON
