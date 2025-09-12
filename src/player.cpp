#include "player.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

void Player::update_pos() {
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
    move_direction.y -= 1;
  }
  if (isKeyPressed(Key::Down) || isKeyPressed(Key::S)) {
    move_direction.y += 1;
  }

  if (move_direction.x != 0.0f || move_direction.y != 0.0f) {
    move_direction = move_direction.normalized();
    move_direction *= speed;
  }
  this->move_vector = move_direction;
}

bool Player::collision_detected(sf::Vector2u window_size) {
  auto player_pos = this->getPosition();

  if (player_pos.x < window_size.x &&
          player_pos.x + this->radius > window_size.x ||
      player_pos.y < window_size.y &&
          player_pos.y + this->radius > window_size.y) {
    return true;
  }
  return false;
}
