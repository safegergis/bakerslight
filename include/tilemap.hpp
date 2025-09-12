#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Tilemap : public sf::Drawable, public sf::Transformable {
private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
  bool load(const std::filesystem::path &tileset, sf::Vector2u tilesize,
            const int *tiles, unsigned int width, unsigned int height);
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};
