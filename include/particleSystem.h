#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    std::vector<Particle> particles;
    sf::VertexArray vertices;
    sf::Time lifetime;
    sf::Vector2f emitter;
    
    void resetParticle(size_t index);

private:

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:

    ParticleSystem(unsigned int count);

    void setEmitter(sf::Vector2f position);

    void update(sf::Time elapsed);
};
