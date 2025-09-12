#include "player.hpp"
#include "tilemap.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode({512, 256}), "CMake SFML Project");
  window.setFramerateLimit(60);

  Player player{};
  constexpr std::array level = {
      0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3,
      3, 3, 3, 3, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1,
      1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 1, 0, 3, 0, 2, 2,
      0, 0, 1, 1, 1, 1, 2, 0, 2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1,
      1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
  };
  Tilemap map;
  if (!map.load("assets/tiles.png", {16, 16}, level.data(), 9, 9))
    return -1;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear();

    // draw everything here

    player.update_pos();
    player.move(player.get_move_vector());
    window.draw(map);
    window.draw(player);

    window.display();
  }
}
