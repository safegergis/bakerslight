#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

struct Transform {
  sf::Vector2f position{0.f, 0.f};
  sf::Vector2f scale{1.f, 1.f};
  float rotation = 0.f;
};

typedef sf::Vector2f Position;

struct Velocity {
  float x, y;
  float maxSpeed = 200.f;
};

struct Sprite {
  sf::CircleShape shape;
  sf::Color color;

  Sprite(float radius, sf::Color col) : color(col) {
    shape.setRadius(radius);
    shape.setFillColor(color);
  }
  // sf::Texture texture;
  // sf::Sprite *sprite{};

  // Sprite(const std::string &texturePath) {
  //   if (texture.loadFromFile(texturePath)) {
  //     sprite->setTexture(texture);
  //   }
  // }
};

struct Player {};
struct Enemy {
  float detectionRange = 150.f;
};

struct Health {
  int current = 100;
  int max = 100;
  bool isDead() const { return current <= 0; }
};

struct Collision {
  sf::FloatRect bounds;
  bool solid = true;

  void updateBounds(const sf::Vector2f &pos, const sf::Vector2f &size) {
    bounds = sf::FloatRect({pos.x, pos.y}, {size.x, size.y});
  }
};

struct PlayerInput {
  bool up = false, down = false, left = false, right = false;
  bool attacking = false;
};

enum class AIType { FollowPlayer, Patrol, Stationary };

struct AI {
  AIType type = AIType::FollowPlayer;
  sf::Vector2f target{0.f, 0.f};
  float detectionRange = 150.f;
  float attackRange = 50.f;
};

struct Weapon {
  float damage = 10.f;
};
