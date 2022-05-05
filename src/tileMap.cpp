#include "tileMap.h"

TileMap::TileMap()
{
    ;
}

TileMap::~TileMap()
{
    ;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;

    // states.shaders and states.blendMode

    target.draw(vertexArray, states);
}

bool TileMap::load(const std::string & tileset, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height)
{
    if (!this->texture.loadFromFile(tileset))
        return false;

    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(width * height * 4); // to accomidate all texture tiles

    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the which tile the user wants in array, with math while avoiding 2d arrays 
            int tileNumber = tiles[i + j * width];

            // get tile in tileset, with math, mod for horizontal and slash with for vertical
            int tileHorizontal = tileNumber % (this->texture.getSize().x / tileSize.x);
            int tileVertical = tileNumber / (this->texture.getSize().x / tileSize.x);

            sf::Vertex * quad = &vertexArray[(i + j * width) * 4];

            // corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // texture coordinates
            quad[0].texCoords = sf::Vector2f(tileHorizontal * tileSize.x, tileVertical * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tileHorizontal + 1) * tileSize.x, tileVertical * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tileHorizontal + 1) * tileSize.x, (tileVertical + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tileHorizontal * tileSize.x, (tileVertical + 1) * tileSize.y);
        }
    }

    return true;
}
