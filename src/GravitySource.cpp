#include "GravitySource.h"

GravitySource::GravitySource(sf::Vector2f position, float strength) : position(position), strength(strength) {}

GravitySource::~GravitySource() = default;

void GravitySource::set_draw(bool draw) {
    this->draw = draw;
}
