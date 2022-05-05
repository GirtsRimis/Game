#include "player.h"

Player::Player()
{
    if (!this->texture.loadFromFile("../resources/tileset.png"))
        std::cout << "Could not load texture!\n";

    this->setTexture(this->texture);

    playerTextureLine = textureY / 2;

    for (int i = 0; i < 9; ++i)
    {
        if (i != 0)
            playerTexture[i] = textureSize * i;
        else
            playerTexture[i] = 0;
    }
}

void Player::animateMovement(const MovementDirection & direction)
{
    switch (direction)
    {
        case MovementDirection::Up:
            acceleration.y -= speed;
            break;
        
        case MovementDirection::Down:
            acceleration.y += speed;
            break;

        case MovementDirection::Right:
            acceleration.x += speed;
            break;

        case MovementDirection::Left:
            acceleration.x -= speed;
            break;

        default:
            break;
    }

    velocity += acceleration;

    if (velocity.x != 0.f && velocity.y != 0.f)
        velocity /= std::sqrt(2.f); 

    velocity *= dampen;

    acceleration = {0.f, 0.f};

    if (velocity.y < 0.f)
    {
        // Up
        this->setTextureRect(sf::IntRect(playerTexture[3], playerTextureLine, textureSize, textureSize));
    }
    else if (velocity.y > 0.f)
    {
        // Down 
        this->setTextureRect(sf::IntRect(playerTexture[5], playerTextureLine, textureSize, textureSize));
    }
    else if (velocity.x > 0.f)
    {
        // Right
        this->setTextureRect(sf::IntRect(playerTexture[8], playerTextureLine, textureSize, textureSize));
    }
    else if (velocity.x < 0.f)
    {
        // Left
        this->setTextureRect(sf::IntRect(playerTexture[0], playerTextureLine, textureSize, textureSize));
    }

    if (velocity.y < 0.f && velocity.x > 0.f)
    {
        // UpRight
        this->setTextureRect(sf::IntRect(playerTexture[2], playerTextureLine, textureSize, textureSize));
    }
    else if (velocity.y < 0.f && velocity.x < 0.f)
    {
        // UpLeft
        this->setTextureRect(sf::IntRect(playerTexture[1], playerTextureLine, textureSize, textureSize));
    }
    else if (velocity.y > 0.f && velocity.x > 0.f)
    {
        // DownRight
        this->setTextureRect(sf::IntRect(playerTexture[7], playerTextureLine, textureSize, textureSize));
    }
    else if (velocity.y > 0.f && velocity.x < 0.f)
    {
        // DownLeft
        this->setTextureRect(sf::IntRect(playerTexture[6], playerTextureLine, textureSize, textureSize));
    }

    this->move(velocity);
}

void Player::idle()
{
    // Idle
    this->setTextureRect(sf::IntRect(playerTexture[4], playerTextureLine, textureSize, textureSize));
}
