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

// TODO: should I use curly braces here?
extern const float GRAV_CONST { 9.8 };
const double       PART_SPAWN_RATE { 30 }; // per second
const double       GRAV_SPAWN_RATE { 2 };
const bool         TRACE { false };

int main()
{
    std::cout << "INITIALIZING gravitas" << std::endl;
    std::cout << "CWD IS: " << std::filesystem::current_path() << std::endl;
    auto app = new App(1920u, 1080u);
    app->run();
}

