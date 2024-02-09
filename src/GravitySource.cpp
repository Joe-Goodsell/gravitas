#include "GravitySource.h"
#include <iostream>

GravitySource::GravitySource(sf::Vector2f position, float strength) : position(position), strength(strength) {
    std::cout << "INITIALISING GRAV SOURCE AT " << position.x << " " << position.y << std::endl;
    create_shape();
}

GravitySource::~GravitySource() = default;

sf::Vector2f GravitySource::get_position() { return this->position; }

float GravitySource::get_strength() { return this->strength; }

void GravitySource::create_shape() { 
    sprite.setRadius(20);
    sprite.setPointCount(4); // turns circle into square
    sprite.setFillColor(sf::Color::Transparent); 
    sprite.setOutlineThickness(2);
    sprite.setOutlineColor(sf::Color::Cyan);
    sprite.setPosition(position);
}

void GravitySource::set_disp(bool disp) {
    this->disp = disp;
}

void GravitySource::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
