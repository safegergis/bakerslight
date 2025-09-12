#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

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
    player.setOrigin({50.f, 50.f});
    window.draw(player);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      player.move({0.1f, 0.f});
    }
    window.display();
  }
}
