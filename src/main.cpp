#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(60);

  Player player{};

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear();

    // draw everything here

    window.draw(player);

    {
      using namespace sf::Keyboard;
      float speed_base = 2.0f;
      float speed_modifier = 1.0f;
      sf::Vector2f move_direction = {0.0f, 0.0f};

      if (isKeyPressed(Key::RShift) || isKeyPressed(Key::LShift)) {
        speed_modifier = 2.0f;
      }
      float speed = speed_base * speed_modifier;

      if (isKeyPressed(Key::Right) || isKeyPressed(Key::D)) {
        move_direction.x += 1;
      }
      if (isKeyPressed(Key::Left) || isKeyPressed(Key::A)) {
        move_direction.x -= 1;
      }
      if (isKeyPressed(Key::Up) || isKeyPressed(Key::W)) {
        player.move({0.f, -1.f});
        move_direction.y -= 1;
      }
      if (isKeyPressed(Key::Down) || isKeyPressed(Key::S)) {
        move_direction.y += 1;
      }

      if (move_direction.x != 0.0f || move_direction.y != 0.0f) {
        move_direction = move_direction.normalized();
        move_direction *= speed;
        player.move(move_direction);
      }
    }
    window.display();
  }
}
