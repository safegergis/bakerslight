#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <typeindex>
#include <unordered_map>

/**
 * Component base
 */
struct Component {
  virtual ~Component() = default;
};

/**
 * Shared components
 */
struct Transform : Component {
  sf::Vector2f position{0.f, 0.f};
  sf::Vector2f scale{1.f, 1.f};
  float rotation = 0.f;
};

struct Velocity : Component {
  sf::Vector2f velocity{0.f, 0.f};
  float maxSpeed = 100.f;
};

struct Sprite : Component {
  sf::Texture texture;
  sf::Sprite *sprite{};

  Sprite(const std::string &texturePath) {
    if (texture.loadFromFile(texturePath)) {
      sprite->setTexture(texture);
    }
  }
};

struct Health : Component {
  int current = 100;
  int maximum = 100;
  bool isDead() const { return current <= 0; }
};

struct Collision : Component {
  sf::FloatRect bounds;
  bool solid = true;

  void updateBounds(const sf::Vector2f &pos, const sf::Vector2f &size) {
    bounds = sf::FloatRect({pos.x, pos.y}, {size.x, size.y});
  }
};

struct PlayerInput : Component {
  bool up = false, down = false, left = false, right = false;
  bool attacking = false;
};

enum class AIType { FollowPlayer, Patrol, Stationary };

struct AI : Component {
  AIType type = AIType::FollowPlayer;
  sf::Vector2f target{0.f, 0.f};
  float detectionRange = 150.f;
  float attackRange = 50.f;
};

struct Weapon : Component {
  float damage = 10.f;
};

class Entity {
private:
  static uint32_t nextId;
  uint32_t id;
  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

public:
  Entity() : id(nextId++) {}

  uint32_t getId() const { return id; }

  template <typename T, typename... Args> T &addComponent(Args &&...args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T &ref = *component;
    components[std::type_index(typeid(T))] = std::move(component);
  }

  template <typename T> T *getComponent() {
    auto it = components.find(std::type_index(typeid(T)));

    if (it != components.end()) {
      return static_cast<T *>(it->second.get());
    }
    return nullptr;
  }

  template <typename T> bool hasComponent() const {
    return components.find(std::type_index(typeid(T))) != components.end();
  }

  template <typename T> void removeComponent() {
    components.erase(std::type_index(typeid(T)));
  }
};

uint32_t Entity::nextId = 0;
