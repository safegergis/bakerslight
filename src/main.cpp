#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear();

    // draw everything here

    sf::CircleShape player(50.0);
    player.setFillColor(sf::Color(150, 50, 250));
    window.draw(player);
    window.display();
  }
}
