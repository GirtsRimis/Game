#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MovableEntity
{
private:
    sf::CircleShape circle;
    sf::Vector2f position;
public:
    MovableEntity(float radius, std::size_t pointCount, sf::Vector2f position);
    
    ~MovableEntity();

    sf::CircleShape getDrawing() const;

    void moveInBounds(sf::RenderWindow & window);

    friend std::ostream & operator << (std::ostream & out, const MovableEntity & entity);
};