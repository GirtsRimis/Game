#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// enum MovementDirection
// {
//     Up = 0,
//     Down = 1,
//     Right = 2,
//     Left = 3,
// };

class Enemy : public sf::Sprite
{
private:
    sf::Texture texture;
    const int textureSize = 32;
    const int textureX = 288;
    const int textureY = 64;
    int enemyTexture[9];
    int enemyTextureLine = 0;

    sf::Vector2f velocity = {0.f, 0.f};
    sf::Vector2f acceleration = {0.f, 0.f};
    float speed = 0.05f;
    float dampen = 0.2f;

public:
    Enemy();
    // void animateMovement(const MovementDirection & direction);
    void idle();
    void pathFind(sf::Vector2f position);
};
