#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <deque>
#include <iostream>
#include <filesystem>
#include <string>
#include "Particle.h"

int main()
{
    std::cout << "INITIALIZING gravitas" << std::endl;
    std::cout << "CWD IS: " << std::filesystem::current_path() << std::endl;
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);


    auto prev_timepoint = std::chrono::high_resolution_clock::now();
    auto prev_fps_diffs = std::deque<std::chrono::duration<double, std::milli>>();
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

    Particle particle = Particle(sf::Vector2f(350,350), sf::Vector2f(0.2,0.2), 0.2f);
    particle.set_trace(true);
    // add some test particles
    particles.push_back(particle);


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
        std::chrono::duration<double, std::milli> elapsed = now - prev_timepoint;
        prev_fps_diffs.push_back(elapsed); 
        if (fps_buff_count >= 10) {
            prev_fps_diffs.pop_front();
        } else {
            fps_buff_count++;
        }

        // TODO: improve inefficient  average
        double fps = 0.0;
        for (int i = 0; i < fps_buff_count - 1; i++) {
            fps += prev_fps_diffs[i].count();
        }
        fps = fps / fps_buff_count;
        prev_timepoint = now;


        window.clear();

        fpsDispText.setString(std::to_string(fps) + " fps");
        window.draw(fpsDispText);
        
        // Let's start with simple for-loop through particles
        for (std::vector<Particle>::iterator iter = particles.begin(); iter != particles.end(); ++iter) {
            iter->update_position();
            iter->draw(window);
        }

        window.display();
    }
}