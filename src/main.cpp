#include "player.hpp"
#include "tilemap.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <entt/entt.hpp>

sf::Vector2u window_size = {512, 256};

class Game {
private:
  sf::RenderWindow window;
  entt::registry registry;
  sf::Clock clock;

public:
  Game() : window(sf::VideoMode(), "Game") {
    // createPlayer();
    // createEnemies();
  }

  void run() {
    while (window.isOpen()) {
      float dt = clock.restart().asSeconds();

      // handleEvents();
      // update(dt);
      // render();
    }
  }
};

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode(window_size), "CMake SFML Project");
  window.setFramerateLimit(60);

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

  Player player{};
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
    if (player.is_colliding_window(window_size)) {
      player.move(-player.get_move_vector());
    }
    window.draw(map);
    window.draw(player);

    window.display();
  }
}
