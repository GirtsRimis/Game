#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <cmath>
#include <X11/Xlib.h>

#include "player.h"
#include "movableEntity.h"
#include "particleSystem.h"
#include "tileMap.h"
#include "levels.h"
#include "enemy.h"

struct ControlLogic
{
    sf::RenderWindow window;
    sf::View view;
    Player playerSprite;
    Enemy enemySprite;
};

std::mutex lockGuard;

void renderingThread(ControlLogic * logicContoller)
{
    std::lock_guard<std::mutex> lock(lockGuard);

    // std::vector<MovableEntity> entities;
    // for (size_t i = 0; i < 10; i++)
    //     entities.push_back(MovableEntity(30.f, 10, {1.f + i , 1.f + i}));
    
    // auto moveEntities = [&](MovableEntity & entity) { entity.moveInBounds(logicContoller->window); };
    // auto drawEntities = [&](MovableEntity & entity) { logicContoller->window.draw(entity.getDrawing()); };

    // sf::Vertex vertex(sf::Vector2f(10.f, 50.f), sf::Color::Blue, sf::Vector2f(100.f, 100.f));

    // sf::VertexArray triangle(sf::Triangles, 3);
    // sf::Transform transform;

    // transform.rotate(5.f);

    // triangle[0].position = sf::Vector2f(10.f, 10.f);
    // triangle[1].position = sf::Vector2f(100.f, 10.f);
    // triangle[2].position = sf::Vector2f(100.f, 100.f);

    // triangle[0].color = sf::Color::Red;
    // triangle[1].color = sf::Color::Blue;
    // triangle[2].color = sf::Color::Green;

    TileMap map;
    if (!map.load("../resources/tileset.png", sf::Vector2u(32, 32), level, 52, 29)) // /home/girts/Dev/C++/Game
        std::cout << "Could not load tileset!\n";

    // ParticleSystem particles(1000);
    // sf::Clock clock;

    // particles.setEmitter({600.f, 700.f});

    logicContoller->window.setActive(true);
    while (logicContoller->window.isOpen())
    {
        // sf::Time elapsed = clock.restart();
        // particles.update(elapsed);
        // std::for_each(entities.begin(), entities.end(), moveEntities);
        logicContoller->window.clear();
        logicContoller->window.draw(map);
        logicContoller->window.draw(logicContoller->playerSprite);
        logicContoller->window.draw(logicContoller->enemySprite);
        // logicContoller->window.draw(player);
        // std::for_each(entities.begin(), entities.end(), drawEntities);
        // logicContoller->window.draw(triangle, transform);
        // logicContoller->window.draw(entity);
        // logicContoller->window.draw(particles);
        logicContoller->window.setView(logicContoller->view);
        logicContoller->window.display();
    }
}

int main()
{
    XInitThreads(); // Needed for multithreading in SFML

    ControlLogic logicContoller;
    logicContoller.window.create(sf::VideoMode(1600, 900), "Game");

    logicContoller.window.setVerticalSyncEnabled(true);
    logicContoller.window.setActive(false);

    logicContoller.view.setCenter(800.f, 450.f);
    logicContoller.view.setSize(1600.f, 900.f);
    // view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f)); // Get another view area, ex. minimap

    std::thread renderThread(&renderingThread, &logicContoller);

    logicContoller.window.setKeyRepeatEnabled(true);

    while (logicContoller.window.isOpen())
    {
        sf::Event event;
        while (logicContoller.window.pollEvent(event))
        {
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                logicContoller.window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::Closed)
            {
                logicContoller.window.close();
                renderThread.join();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            logicContoller.playerSprite.animateMovement(MovementDirection::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            logicContoller.playerSprite.animateMovement(MovementDirection::Down);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            logicContoller.playerSprite.animateMovement(MovementDirection::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            logicContoller.playerSprite.animateMovement(MovementDirection::Left);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            logicContoller.view.setSize(1600.f, 900.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            logicContoller.view.setSize(533.333333333f, 300.f);
        }

        logicContoller.enemySprite.pathFind(logicContoller.playerSprite.getPosition());
    }

    return 0;
}