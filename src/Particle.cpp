#include "Particle.h"
#include "Utils.h"
#include <chrono>
#include <SFML/System/Vector2.hpp>


Particle::Particle(sf::Vector2f position, sf::Vector2f direction, float velocity) : position(position), direction(direction), velocity(velocity) {
    sprite.setFillColor(sf::Color::White);
    // TODO: make not hard coded
    sprite.setPosition(position);
    sprite.setRadius(50.f);
}


Particle::~Particle() = default;

sf::Vector2f Particle::update_position(sf::Vector2f external_force_direction, float external_force_strength) {
    auto internal = this->velocity * utils::normalize2f(this->direction);
    auto external = external_force_strength * utils::normalize2f(external_force_direction);

    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - this->last_update);
    this->last_update = now;

    auto new_position = this->position + static_cast<float>(elapsed_seconds.count())*(internal + external);
    this->position = new_position;
    sprite.setPosition(new_position);
    return new_position;
}

sf::Vector2f Particle::update_position() {
    return this->update_position(sf::Vector2f(0,0),0);
}

void Particle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}