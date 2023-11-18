#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
sf::Text createMenuText(const std::string& text, const sf::Font& font, int x,
                        int y);
float handleMenu(sf::RenderWindow& menuWindow, sf::Text& easy, sf::Text& medium,
                 sf::Text& hard);
void handleGame(sf::RenderWindow& window, float delay, sf::Vector2f& direction,
                std::vector<sf::Vector2f>& snake, sf::Vector2f& foodPosition);