#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Player : public sf::Drawable, public sf::Transformable {
private:
  sf::CircleShape sprite;
  sf::Vector2f move_vector;

public:
  Player() {
    sprite.setRadius(50.0f);
    sprite.setFillColor(sf::Color(150, 50, 250));
  }
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    states.transform *= getTransform();
    target.draw(sprite, states);
  }

  void update_pos();

  sf::Vector2f get_move_vector() { return move_vector; }
};
