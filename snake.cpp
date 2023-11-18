#include "snake.hpp"

// Function to create a text object for the menu
sf::Text createMenuText(const std::string& text, const sf::Font& font, int x,
                        int y) {
  sf::Text menuText(text, font, 50);
  menuText.setPosition(x, y);
  return menuText;
}

// Function to handle the menu logic
float handleMenu(sf::RenderWindow& menuWindow, sf::Text& easy, sf::Text& medium,
                 sf::Text& hard) {
  float delay = 0.1f;
  sf::Event event;
  while (menuWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) menuWindow.close();

    // Check if the user has clicked on one of the difficulty levels
    if (event.type == sf::Event::MouseButtonPressed) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(menuWindow);

      if (easy.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        delay = 0.2f;
        menuWindow.close();
      } else if (medium.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        delay = 0.1f;
        menuWindow.close();
      } else if (hard.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        delay = 0.05f;
        menuWindow.close();
      }
    }
  }
  return delay;
}

// Function to handle the game logic
void handleGame(sf::RenderWindow& window, float delay, sf::Vector2f& direction,
                std::vector<sf::Vector2f>& snake, sf::Vector2f& foodPosition) {
  sf::Clock clock;
  sf::Event event;
  int stepSize = 10;
  int initialSize = 10;
  int size = initialSize;  // Current size of the snake and food
  int foodEaten = 0;       // Number of food eaten by the snake
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      // Handle keyboard e`vents
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
          direction = sf::Vector2f(0, -1);
        else if (event.key.code == sf::Keyboard::Down)
          direction = sf::Vector2f(0, 1);
        else if (event.key.code == sf::Keyboard::Left)
          direction = sf::Vector2f(-1, 0);
        else if (event.key.code == sf::Keyboard::Right)
          direction = sf::Vector2f(1, 0);
      }
    }

    if (clock.getElapsedTime().asSeconds() > delay) {
      clock.restart();

      // Move the snake
      for (size_t i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
      }
      snake[0] += direction;
      float collisionRadius = 10.0f;  // Adjust this value as needed

      // Calculate the distance between the snake's head and the food
      sf::Vector2f diff = snake[0] - foodPosition;
      float distance = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));

      // Check if the distance is less than the collision radius
      if (distance < collisionRadius) {
        // The snake has eaten the food
        snake.push_back(sf::Vector2f());
        snake.push_back(sf::Vector2f());
        foodEaten++;
        size = initialSize * foodEaten;
        // Move the food to a new random position
        foodPosition =
            sf::Vector2f((rand() % (window.getSize().x / stepSize)) * stepSize,
                         (rand() % (window.getSize().y / stepSize)) * stepSize);
      }

      // Check for collision with itself
      for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[0] == snake[i]) {
          // Game over
          window.close();
        }
      }
    }
    window.clear();

    // Draw the snake
    for (const auto& segment : snake) {
      sf::RectangleShape rectangle(sf::Vector2f(size, size));
      rectangle.setPosition(segment);
      window.draw(rectangle);
    }

    // Draw the food
    sf::CircleShape circle(5);
    circle.setPosition(foodPosition);
    window.draw(circle);

    // Display the window
    window.display();
  }
}
