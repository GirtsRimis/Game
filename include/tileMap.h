#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:

    sf::VertexArray vertexArray;
    sf::Texture texture;

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
    TileMap();
    ~TileMap();
    
    bool load(const std::string & tileset, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height);
};
