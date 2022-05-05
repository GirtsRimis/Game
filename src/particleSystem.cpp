#include "particleSystem.h"

void ParticleSystem::resetParticle(size_t index)
{
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    vertices[index].position = emitter;
}

void ParticleSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = NULL;

    // states.shaders and states.blendMode

    target.draw(vertices, states);
}

ParticleSystem::ParticleSystem(unsigned int count)
    : particles(count)
    , vertices(sf::Points, count)
    , lifetime(sf::seconds(3.f))
    , emitter(0.f, 0.f)
{
    ;
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
    emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
    for (size_t i = 0; i < particles.size(); ++i)
    {
        Particle & p = particles[i];
        p.lifetime -= elapsed;

        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        vertices[i].position += p.velocity * elapsed.asSeconds();

        float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
        vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}
