#include "movableEntity.h"

MovableEntity::MovableEntity(float radius, std::size_t pointCount, sf::Vector2f position)
{
    this->circle.setRadius(radius);
    this->circle.setPointCount(pointCount);
    this->circle.setFillColor(sf::Color::Red);
    this->position = position;
    this->circle.setPosition(this->position);
}

MovableEntity::~MovableEntity()
{
    ;
}

sf::CircleShape MovableEntity::getDrawing() const
{
    return this->circle;
}

void MovableEntity::moveInBounds(sf::RenderWindow & window)
{
    if (this->circle.getPosition().x + this->circle.getRadius() * 2 > window.getSize().x)
        this->position.x *= -1.f;

    if (this->circle.getPosition().x < 0)
        this->position.x *= -1.f;

    if (this->circle.getPosition().y + this->circle.getRadius() * 2 > window.getSize().y)
        this->position.y *= -1.f;

    if (this->circle.getPosition().y < 0)
        this->position.y *= -1.f;

    this->circle.move(this->position);
}

std::ostream & operator << (std::ostream & out, const MovableEntity & entity)
{
    out << "pos x: " << entity.circle.getPosition().x << " | pos y: " << entity.circle.getPosition().y << "\n";
    return out;
}
