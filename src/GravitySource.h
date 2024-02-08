#ifndef GRAVITY_SOURCE_H
#define GRAVITY_SOURCE_H

#include "SFML/System/Vector2.hpp"
class GravitySource {
    public:
        GravitySource(sf::Vector2f position, float strength);
        ~GravitySource();

        void set_draw(bool draw);
    
    private:
        sf::Vector2f position;
        float strength;
        bool draw;
};

#endif