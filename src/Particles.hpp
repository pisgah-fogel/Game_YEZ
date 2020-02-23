#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "RessourcesManager.hpp"
#include "Log.hpp"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    /**
     * @brief Construct a new Particle System object
     * 
     * @param texid Texture id (registered in the ressourceManager)
     * @param count Number of particles
     */
    ParticleSystem(unsigned int texid, unsigned int count) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(3)),
    m_emitter(0, 0)
    {
        m_texture = core::RessourcesManager::getInstance()->getTexture(texid);
		if (!m_texture) {
			LOG("Error cannot get texture, abord");
		}
    }

    ~ParticleSystem() {
        LOG("Debug ParticleSystem is freed");
    }

    /**
     * @brief Set the position of particles source
     * 
     * @param position 2D position of the particles source
     */
    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    /**
     * @brief Update particules
     * 
     * @param elapsed Elaspsed time since the last update
     */
    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, states);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    /**
     * @brief Reset particule
     *
     * This function is called after a particle has
     * reached its lifetime
     * 
     * @param index Index in the particule vector of the particule to reset
     */
    void resetParticle(std::size_t index)
    {
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    sf::Texture* m_texture;
};

#endif // PARTICLES_HPP
