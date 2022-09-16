#include "enemy.h"

Enemy::Enemy()
{
    if (!this->texture.loadFromFile("../resources/tileset.png"))
        std::cout << "Could not load texture!\n";

    this->setTexture(this->texture);

    enemyTextureLine = textureY / 2;

    for (int i = 0; i < 9; ++i)
    {
        if (i != 0)
            enemyTexture[i] = textureSize * i;
        else
            enemyTexture[i] = 0;
    }
}

void Enemy::pathFind(sf::Vector2f position)
{
    if (std::floor(this->getPosition().x) < std::floor(position.x))
        acceleration.x += speed;
    else if (std::floor(this->getPosition().x) > std::floor(position.x))
        acceleration.x -= speed;
    if (std::floor(this->getPosition().y) < std::floor(position.y))
        acceleration.y += speed;
    else if (std::floor(this->getPosition().y) > std::floor(position.y))
        acceleration.y -= speed;

    if (std::floor(this->getPosition().x) == std::floor(position.x) && std::floor(this->getPosition().y) == std::floor(position.y))
        this->idle();

    velocity += acceleration;

    if (velocity.x != 0.f && velocity.y != 0.f)
        velocity /= std::sqrt(2.f); 

    velocity *= dampen;

    acceleration = {0.0f, 0.0f};

    // Up
    if (velocity.y < 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[3], enemyTextureLine, textureSize, textureSize));
    // Down 
    else if (velocity.y > 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[5], enemyTextureLine, textureSize, textureSize));
    // Right
    else if (velocity.x > 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[8], enemyTextureLine, textureSize, textureSize));
    // Left
    else if (velocity.x < 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[0], enemyTextureLine, textureSize, textureSize));

    // UpRight
    if (velocity.y < 0.f && velocity.x > 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[2], enemyTextureLine, textureSize, textureSize));
    // UpLeft
    else if (velocity.y < 0.f && velocity.x < 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[1], enemyTextureLine, textureSize, textureSize));
    // DownRight
    else if (velocity.y > 0.f && velocity.x > 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[7], enemyTextureLine, textureSize, textureSize));
    // DownLeft
    else if (velocity.y > 0.f && velocity.x < 0.f)
        this->setTextureRect(sf::IntRect(enemyTexture[6], enemyTextureLine, textureSize, textureSize));

    this->move(velocity);
}

void Enemy::idle()
{
    // Idle
    this->setTextureRect(sf::IntRect(enemyTexture[4], enemyTextureLine, textureSize, textureSize));
}
