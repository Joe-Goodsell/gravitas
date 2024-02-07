#include <SFML/System.hpp>
#include <cmath>
#include "Utils.h"

namespace utils {
sf::Vector2f normalize2f(const sf::Vector2f& source) {
    float length = std::sqrt((source.x * source.x) + (source.y * source.y));
    if (length == 0.0f) {
        return sf::Vector2f(0,0);
    }
    return sf::Vector2f(source.x / length, source.y / length);
}
}