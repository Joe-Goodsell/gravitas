#include "Particle.h"
#include "Utils.h"
#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <iostream>

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, float mass) : position(position), velocity(velocity), mass(mass) {
    //TODO: add dynamic color
    this->color = sf::Color::Green;
    sprite.setFillColor(color);
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
        std::cout << "velocity-------- " << "x = " << std::to_string(this->velocity.x) << " y = " << std::to_string(this->velocity.y) << std::endl;
    }

    auto external = external_force_strength * utils::normalize2f(external_force_direction);

    // Ccalculate ∆Time
    auto now = std::chrono::high_resolution_clock::now();
    // WARN: this appears to not be correct
    std::chrono::duration<float> delta_t = now - this->last_update;
    this->last_update = now;

    // Newton's 2nd law: ∆p = F x ∆t
    auto old_position = this->get_position();
    auto delta_p = delta_t.count()*utils::normalize2f(external_force_direction)*external_force_strength;
    this->velocity = this->velocity + (delta_p / this->mass);
    auto new_position = old_position + this->velocity;
    this->set_position(new_position);

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

float const Particle::get_mass() { return this->mass; }

void Particle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}