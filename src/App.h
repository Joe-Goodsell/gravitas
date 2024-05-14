#ifndef GRAVITAS_APP_H
#define GRAVITAS_APP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GravitySource.h"
#include "Particle.h"

class App {
public:
    App(unsigned int width, unsigned int height);
    ~App();
    void run();


private:
    const float GRAV_CONST { 9.8 };
    const double PART_SPAWN_RATE { 30 }; // per second
    const double GRAV_SPAWN_RATE { 2 };
    const bool TRACE { false };
    int windowHeight;
    int windowWidth;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text fpsDispText;
    std::vector<GravitySource> gravSources;
    std::vector<Particle> particles;
    void createWindow(unsigned int width, unsigned int height);
    void loadFont();
    void setFpsText();
    void initializeParticles();
    void initializeGravSources();
    bool update(Particle& particle);
};

#endif //GRAVITAS_APP_H