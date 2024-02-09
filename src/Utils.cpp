#include <SFML/System.hpp>
#include <cmath>
#include "Utils.h"

namespace utils {
sf::Vector2f normalize2f(const sf::Vector2f& source) {
    float norm = magnitude2f(source);
    if (norm == 0.0f) {
        return sf::Vector2f(0,0);
    }
    return sf::Vector2f(source.x / norm, source.y / norm);
}

float magnitude2f(const sf::Vector2f& source) {
    return std::sqrt((source.x * source.x) + (source.y * source.y));
}
}