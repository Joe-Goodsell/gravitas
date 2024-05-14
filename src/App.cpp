//
// Created by Joseph Goodsell on 14/5/2024.
//

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <chrono>
#include <deque>
#include <iostream>
#include <filesystem>
#include <string>
#include "Particle.h"
#include "GravitySource.h"
#include "Utils.h"
#include "App.h"
 App::App(unsigned int width, unsigned int height) : window(sf::RenderWindow({width, height}, "CMake SFML Project")), windowWidth(width), windowHeight(height) {
    this->window.setFramerateLimit(144);
    loadFont();
    setFpsText();
    initializeParticles();
    initializeGravSources();
}

App::~App() {
    std::cout << "closing app" << std::endl;
}

void App::run() {
    auto prev_timepoint = std::chrono::high_resolution_clock::now();
    auto prev_fps_diffs = std::deque<double>();
    int fps_buff_count = 0;
    double grav_spawn_timer = 0;
    double part_spawn_timer = 0;
    while (this->window.isOpen()) {
            for (auto event = sf::Event{}; this->window.pollEvent(event);)
            {
                if (event.type == sf::Event::Closed)
                {
                    this->window.close();
                }
            }

            // Calculate FPS
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - prev_timepoint;
            // DEBUG
            prev_fps_diffs.push_back(elapsed.count());
            if (fps_buff_count >= 10) {
                prev_fps_diffs.pop_front();
            } else {
                fps_buff_count++;
            }

            // TODO: improve inefficient  average
            double avg_diff = 0.0;
            for (int i = 0; i < fps_buff_count - 1; i++) {
                avg_diff += prev_fps_diffs[i];
            }
            // DEBUG
            avg_diff = avg_diff / fps_buff_count;
            double fps = 1 / avg_diff;
            prev_timepoint = now;

            // Check for leftclick
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && part_spawn_timer <= 0) {
                auto mouse_pos = sf::Mouse::getPosition(window);
                std::cout << "RECEIVED LEFTMOUSE AT " << mouse_pos.x << " " << mouse_pos.y << std::endl;
                auto rand1 = static_cast<float>(rand())/RAND_MAX - 0.5;
                auto rand2 = static_cast<float>(rand())/RAND_MAX - 0.5;
                auto p = Particle(sf::Vector2f(mouse_pos.x, mouse_pos.y), 5.f*sf::Vector2f(rand1,rand2), 5.f);
                particles.push_back(p);
                part_spawn_timer = 1 / PART_SPAWN_RATE;
            } else if (part_spawn_timer > 0) {
                part_spawn_timer -= elapsed.count();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && grav_spawn_timer <= 0) {
                auto mouse_pos = sf::Mouse::getPosition(window);
                auto grav_source = GravitySource(sf::Vector2f(mouse_pos.x,mouse_pos.y), 5000.f, 5.f);
                grav_source.set_disp(true);
                this->gravSources.push_back(grav_source);
                grav_spawn_timer = 1 / GRAV_SPAWN_RATE;
            } else if (grav_spawn_timer > 0) {
                grav_spawn_timer -= elapsed.count();
            }

            window.clear();

            // Draw FPS widget
            fpsDispText.setString(std::to_string(fps) + " fps");
            window.draw(fpsDispText);

            for (GravitySource grav : this->gravSources) {
                grav.draw(this->window);
            }

            // NOTE: *should* be O(n)
            this->particles.erase(std::remove_if(particles.begin(), particles.end(), [this](Particle& particle) { return this->update(particle); }), particles.end());
            this->window.display();
    }
}

void App::loadFont() {
    if (!this->font.loadFromFile("../../assets/fonts/dejavu_sans_mono.ttf")) {
        // handle error
    }
}

void App::setFpsText() {
    this->fpsDispText.setCharacterSize(24);
    this->fpsDispText.setFillColor(sf::Color::White);
    this->fpsDispText.setFont(font);
    this->fpsDispText.setPosition(sf::Vector2f(20.f, 20.f));
}

void App::initializeParticles() {
    // add some test particles
    auto randmax = static_cast<float>(RAND_MAX);

    for (int i = 0; i < 50; i++) {
        auto rand1 = static_cast<float>(rand() / randmax) - 0.5;
        auto rand2 = static_cast<float>(rand() / randmax) - 0.5;
        auto p = Particle(sf::Vector2f(350,350), 5.f*sf::Vector2f(rand1,rand2), 5.f);
        p.set_trace(false);
        particles.push_back(p);
    }
}

void App::initializeGravSources() {
    auto grav_source = GravitySource(sf::Vector2f(700,700), 5000.f, 5.f);
    grav_source.set_disp(true);
    this->gravSources.push_back(grav_source);
}

bool App::update(Particle& particle) {
    sf::Vector2f extern_force_direction = sf::Vector2f(0,0);
    float extern_force_magnitude;

    //TODO: add support for multiple grav sources
    // auto p2grav_vec = grav_source.get_position() - particle.get_position() ;
    // // auto p2grav_vec = particle.get_position() - grav_source.get_position();
    // auto dist = std::max(1.f, utils::magnitude2f(p2grav_vec));
    // extern_force_magnitude = (GRAV_CONST * grav_source.get_strength() * particle.get_mass()) / (dist*dist);
    // extern_force_direction = utils::normalize2f(p2grav_vec);


    for (GravitySource grav_source : this->gravSources) {
        auto p2grav_vec = grav_source.get_position() - particle.get_position() ;
        // auto p2grav_vec = particle.get_position() - grav_source.get_position();
        auto dist = std::max(1.f, utils::magnitude2f(p2grav_vec));
        extern_force_magnitude = (GRAV_CONST * grav_source.get_strength() * particle.get_mass()) / (dist*dist);
        extern_force_direction += extern_force_magnitude * utils::normalize2f(p2grav_vec);
    }


    //DEBUG
    // if (TRACE) {
    //     std::cout << "P2_GRAV_VEC " << p2grav_vec.x << " " << p2grav_vec.y << std::endl;
    //     std::cout << "PART_POS " << particle.get_position().x << " " << particle.get_position().y << std::endl;
    //     std::cout << "DIST__ " << dist << std::endl;

    //     //DEBUG
    //     std::cout << "EXTERN_FORCE_DIRECTION  " << extern_force_direction.x << " " << extern_force_direction.y << std::endl;
    //     std::cout << "EXTERN_FORCE_MAGNITUDE  " << extern_force_magnitude << std::endl;
    // }

    // auto position = particle.update_position(extern_force_direction, extern_force_magnitude);

    // TODO: make gravity vector include magnitude
    auto position = particle.update_position(extern_force_direction, 1);

    //DEBUG
    if (TRACE) {
        std::cout << "PARTICLE AT " << position.x << " " << position.y << std::endl;
        std::cout << "OUT OF BOUNDS? " << (position.x > this->windowWidth || position.y > this->windowHeight || position.x < 0 || position.y < 0) << std::endl;
    }

    particle.draw(window);
    return (position.x > this->windowWidth || position.y > this->windowHeight || position.x < 0 || position.y < 0);
}
