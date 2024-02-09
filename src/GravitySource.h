#ifndef GRAVITY_SOURCE_H
#define GRAVITY_SOURCE_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class GravitySource {
    public:
        void set_disp(bool disp);
        void draw(sf::RenderWindow& window);

        GravitySource(sf::Vector2f position, float strength, float mass);
        ~GravitySource();

        sf::Vector2f get_position();
        float get_strength();
    
    private:
        sf::Vector2f position;
        float radius;
        float mass;
        bool disp;
        sf::CircleShape sprite;

        void create_shape();
};

#endif