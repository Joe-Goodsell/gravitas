#ifndef GRAVITY_SOURCE_H
#define GRAVITY_SOURCE_H

#include "SFML/System/Vector2.hpp"
class GravitySource {
    public:
        sf::Vector2f position;
        float strength;

        GravitySource(sf::Vector2f position);
        ~GravitySource();
};

#endif