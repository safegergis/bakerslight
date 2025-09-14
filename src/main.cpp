#include "tilemap.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <components.hpp>
#include <entt/entt.hpp>

sf::Vector2u window_size = {512, 256};

class Game {
private:
  sf::RenderWindow window;
  entt::registry registry;
  sf::Clock clock;
  Tilemap map;
  static constexpr std::array<int, 126> level = {
      0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
      1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3,
      3, 3, 3, 3, 3, 3, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0,
      0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 1, 0,
      3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 2, 0, 1, 0, 3, 0, 2, 2, 2,
      0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1,
  };

public:
  Game() : window(sf::VideoMode(window_size), "Game") {
    window.setFramerateLimit(60);
    createPlayer();
    // createEnemies();
    if (!map.load("assets/tiles.png", {16, 16}, level.data(), 14, 9)) {
      // This is not great, but we don't have proper error handling yet
      window.close();
    }
  }

  void run() {
    while (window.isOpen()) {
      float dt = clock.restart().asSeconds();

      handleEvents();
      update(dt);
      render();
    }
  }

private:
  void createPlayer() {
    auto player = registry.create();
    registry.emplace<Position>(player, 100.f, 100.f);
    registry.emplace<Velocity>(player, 0.f, 0.f);
    registry.emplace<Sprite>(player, 15.f, sf::Color::Blue);
    registry.emplace<Player>(player);
    registry.emplace<Health>(player, 100, 100);
  }

  void createEnemies() {
    // TODO
  }

  void handleEvents() {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() ||
          (event->is<sf::Event::KeyPressed>() &&
           event->getIf<sf::Event::KeyPressed>()->code ==
               sf::Keyboard::Key::Escape)) {
        window.close();
      }
    }
  }

  void update(float dt) {
    inputSystem(dt);
    aiSystem(dt);
    movementSystem(dt);
  }

  void inputSystem(float dt) {
    auto playerView = registry.view<Player, Velocity>();

    for (auto entity : playerView) {
      auto &vel = playerView.get<Velocity>(entity);

      // reset velocity
      vel.x = vel.y = 0.f;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        vel.y -= vel.maxSpeed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        vel.y += vel.maxSpeed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        vel.x -= vel.maxSpeed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        vel.x += vel.maxSpeed;

      // Normalize diagonal movement
      float magnitude = std::sqrt(vel.x * vel.x + vel.y * vel.y);
      if (magnitude > vel.maxSpeed) {
        vel.x = (vel.x / magnitude) * vel.maxSpeed;
        vel.y = (vel.y / magnitude) * vel.maxSpeed;
      }
    }
  }

  void aiSystem(float dt) {
    // TODO
  }

  void movementSystem(float dt) {
    auto view = registry.view<Position, Velocity>();
    for (auto entity : view) {
      auto &pos = view.get<Position>(entity);
      auto &vel = view.get<Velocity>(entity);

      pos.x += vel.x * dt;
      pos.y += vel.y * dt;

      pos.x = std::max(0.f, std::min(pos.x, static_cast<float>(window_size.x)));
      pos.y = std::max(0.f, std::min(pos.y, static_cast<float>(window_size.y)));
    }
  }

  void render() {
    window.clear(sf::Color::Black);
    window.draw(map);

    auto view = registry.view<Position, Sprite>();

    for (auto entity : view) {
      auto &pos = view.get<Position>(entity);
      auto &sprite = view.get<Sprite>(entity);

      sprite.shape.setPosition({pos.x, pos.y});
      window.draw(sprite.shape);
    }

    window.display();
  }
};

int main() {
  Game game;
  game.run();
  return 0;
}
