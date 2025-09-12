#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "player.hpp"

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

    Player player{};
    window.draw(player);
    window.display();
  }
}
