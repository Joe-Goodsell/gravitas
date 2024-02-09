#include "Particle.h"
#include "Utils.h"
#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <iostream>


Particle::Particle(sf::Vector2f position, sf::Vector2f direction, float velocity) : position(position), direction(direction), velocity(velocity) {
    sprite.setFillColor(sf::Color::White);
    // TODO: make not hard coded
    sprite.setPosition(position);
    sprite.setRadius(2.f);
    last_update = std::chrono::high_resolution_clock::now();
}


Particle::~Particle() = default;

sf::Vector2f Particle::update_position(sf::Vector2f external_force_direction, float external_force_strength) {

    // DEBUG 
    if (trace) {
        std::cout << "old position-------- " << "x = " << std::to_string(this->position.x) << " y = " << std::to_string(this->position.y) << std::endl;
    }

    auto internal = this->velocity * utils::normalize2f(this->direction); 
    auto external = external_force_strength * utils::normalize2f(external_force_direction);

    auto now = std::chrono::high_resolution_clock::now();
    // WARN: this appears to not be correct
    std::chrono::duration<float> elapsed_seconds = now - this->last_update;
    this->last_update = now;
    // this->position = this->position + elapsed_seconds.count()*(internal + external);
    auto old_position = this->get_position();
    auto new_position = old_position + elapsed_seconds.count()*(internal+external);
    this->set_position(new_position);

    // DEBUG
    if (trace) {
        std::cout << "extern dir x: " << external_force_direction.x << ", y " << external_force_direction.y << "; magnitude " << external_force_strength << std::endl;
        std::cout << "elapsed: " << elapsed_seconds.count() << std::endl;
        std::cout << "internal: " << "x = " << std::to_string(internal.x) << " y = " << std::to_string(internal.y) << std::endl;
        std::cout << "elapsed_seconds: " << std::to_string(elapsed_seconds.count()) << std::endl;
        std::cout << "new position: " << "x = " << std::to_string(this->position.x) << " y = " << std::to_string(this->position.y) << std::endl;
    }

    return this->position;
}

sf::Vector2f Particle::update_position() {
    return this->update_position(sf::Vector2f(0.f,0.f), 0.f);
}

void Particle::set_trace(bool trace) {
    this->trace = trace;
}

sf::Vector2f const Particle::get_position() { return this->position; }

void Particle::set_position(sf::Vector2f position) {
    this->position = position;
    this->sprite.setPosition(position);
}

void Particle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}