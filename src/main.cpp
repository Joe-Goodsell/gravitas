#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <deque>
#include <iostream>
#include <filesystem>
#include <string>
#include "Particle.h"
#include "GravitySource.h"
#include "Utils.h"

int main()
{
    std::cout << "INITIALIZING gravitas" << std::endl;
    std::cout << "CWD IS: " << std::filesystem::current_path() << std::endl;
    const unsigned int WINDOW_HEIGHT = 1920u, WINDOW_WIDTH = 1080u;
    auto window = sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, "CMake SFML Project" };
    window.setFramerateLimit(144);


    auto prev_timepoint = std::chrono::high_resolution_clock::now();
    auto prev_fps_diffs = std::deque<double>();
    int fps_buff_count = 0;
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/dejavu_sans_mono.ttf")) {
        // handle error
    }
    sf::Text fpsDispText;
    fpsDispText.setString("Hi");
    fpsDispText.setCharacterSize(24);
    fpsDispText.setFillColor(sf::Color::White);
    fpsDispText.setFont(font);
    fpsDispText.setPosition(sf::Vector2f(20.f, 20.f));


    // Initialise particles
    std::vector<Particle> particles;

    Particle particle = Particle(sf::Vector2f(100,100), sf::Vector2f(0.2,0.2), 500.f);
    // add some test particles
    auto randmax = static_cast<float>(RAND_MAX);

    for (int i = 0; i < 50; i++) {
        auto rand1 = static_cast<float>(rand() / randmax) - 0.5;
        auto rand2 = static_cast<float>(rand() / randmax) - 0.5;
        auto p = Particle(sf::Vector2f(350,350), sf::Vector2f(rand1,rand2), 500.f);
        p.set_trace(false);
        particles.push_back(p);
    }


    // Initialise gravity well
    // std::vector<GravitySource> grav_sources;
    // grav_sources.push_back(GravitySource(sf::Vector2f(700,700), 1.f));
    auto grav_source = GravitySource(sf::Vector2f(700,700), 500000.f);
    grav_source.set_disp(true);


    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
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


        window.clear();

        fpsDispText.setString(std::to_string(fps) + " fps");
        window.draw(fpsDispText);

        grav_source.draw(window);
        
        // Let's start with simple for-loop through particles


        auto update = [&window, &grav_source](Particle& particle){ 
            sf::Vector2f extern_force_direction;
            float extern_force_magnitude;

            //TODO: add support for multiple grav sources
            // auto p2grav_vec = grav_source.get_position() - particle.get_position() ;
            auto p2grav_vec = particle.get_position() - grav_source.get_position();
            auto magnitude = std::max(1.f, utils::magnitude2f(p2grav_vec));
            extern_force_magnitude = (10.f / (magnitude*magnitude)) * grav_source.get_strength();
            extern_force_direction = utils::normalize2f(p2grav_vec);

            
            //DEBUG
            std::cout << "P2_GRAV_VEC " << p2grav_vec.x << " " << p2grav_vec.y << std::endl;
            std::cout << "PART_POS " << particle.get_position().x << " " << particle.get_position().y << std::endl;
            std::cout << "DIST__ " << magnitude << std::endl;

            //DEBUG
            std::cout << "EXTERN_FORCE_DIRECTION  " << extern_force_direction.x << " " << extern_force_direction.y << std::endl;
            std::cout << "EXTERN_FORCE_MAGNITUDE  " << extern_force_magnitude << std::endl;

            auto position = particle.update_position(extern_force_direction, extern_force_magnitude); 
            
            //DEBUG
            std::cout << "PARTICLE AT " << position.x << " " << position.y << std::endl;
            std::cout << "OUT OF BOUNDS? " << (position.x > WINDOW_WIDTH || position.y > WINDOW_HEIGHT || position.x < 0 || position.y < 0) << std::endl;

            particle.draw(window); 
            return (position.x > WINDOW_WIDTH || position.y > WINDOW_HEIGHT || position.x < 0 || position.y < 0);
        };

        // NOTE: *should* be O(n)
        particles.erase(std::remove_if(particles.begin(), particles.end(), update), particles.end());

        window.display();
    }
}