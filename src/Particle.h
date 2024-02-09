// src/Particle.h
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
    public:

        Particle(sf::Vector2f position, sf::Vector2f direction, float velocity);
        ~Particle();

        sf::Vector2f update_position(sf::Vector2f external_force_direction, float external_force_strength);
        sf::Vector2f update_position();
        void set_trace(bool trace);
        sf::Vector2f const get_position();
        void set_position(sf::Vector2f position);

        void draw(sf::RenderWindow& window);

    private:
        sf::Vector2f position;
        sf::Vector2f direction;
        float velocity;
        sf::CircleShape sprite;
        sf::Color color;
        bool trace;
        std::chrono::time_point<std::chrono::high_resolution_clock> last_update;
};
#endif