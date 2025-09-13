#pragma once
#include "components.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

class System {
public:
  virtual ~System() = default;
  virtual void update(std::vector<std::unique_ptr<Entity>> &entities,
                      float deltaTime) = 0;
};

class InputSystem : public System {
public:
  void update(std::vector<std::unique_ptr<Entity>> &entities,
              float deltaTime) override {
    for (auto &entity : entities) {
      auto input = entity->getComponent<PlayerInput>();
      auto velocity = entity->getComponent<Velocity>();

      if (!input || !velocity)
        continue;

      // Reset velocity
      velocity->velocity = {0.f, 0.f};

      // NOTE: This prob needs adjusting
      if (input->up)
        velocity->velocity.y -= velocity->maxSpeed;
      if (input->down)
        velocity->velocity.y += velocity->maxSpeed;
      if (input->left)
        velocity->velocity.x -= velocity->maxSpeed;
      if (input->right)
        velocity->velocity.x += velocity->maxSpeed;
    }
  }
};
