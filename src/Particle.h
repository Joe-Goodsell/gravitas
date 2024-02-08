// src/Particle.h
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
    public:
        sf::Vector2f position;
        sf::Vector2f direction;
        float velocity;
        // float mass;

        Particle(sf::Vector2f position, sf::Vector2f direction, float velocity);
        ~Particle();

        sf::Vector2f update_position(sf::Vector2f external_force_direction, float external_force_strength);
        sf::Vector2f update_position();
        void set_trace(bool trace);

        void draw(sf::RenderWindow& window);

    private:
        sf::CircleShape sprite;
        bool trace;


        std::chrono::time_point<std::chrono::high_resolution_clock> last_update;
};
#endif