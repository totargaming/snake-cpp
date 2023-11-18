#include "snake.hpp"
int main() {
  // Create a window for the menu
  sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Snake Game - Menu");

  // Create text objects for each difficulty level
  sf::Font font;
  font.loadFromFile(
      "/usr/share/fonts/truetype/fonts-gujr-extra/aakar-medium.ttf");  // Replace
                                                                       // with
                                                                       // the
                                                                       // path
                                                                       // to
                                                                       // your
                                                                       // font
                                                                       // file

  sf::Text easy = createMenuText("Easy", font, 350, 200);
  sf::Text medium = createMenuText("Medium", font, 350, 300);
  sf::Text hard = createMenuText("Hard", font, 350, 400);

  sf::Vector2f direction(1, 0);  // Start moving to the right

  // Create a vector to hold the positions of each segment of the snake
  std::vector<sf::Vector2f> snake;
  snake.push_back(
      sf::Vector2f(100, 100));  // Start the snake at position (100, 100)

  // Create a variable to hold the position of the food
  sf::Vector2f foodPosition(200, 200);  // Start the food at position (200, 200)

  float delay = 0.1f;

  while (menuWindow.isOpen()) {
    delay = handleMenu(menuWindow, easy, medium, hard);

    // Draw the menu
    menuWindow.clear();
    menuWindow.draw(easy);
    menuWindow.draw(medium);
    menuWindow.draw(hard);
    menuWindow.display();
  }

  // Create a window for the game
  sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

  while (window.isOpen()) {
    handleGame(window, delay, direction, snake, foodPosition);
  }

  return 0;
}