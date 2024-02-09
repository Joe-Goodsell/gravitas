#include <gtest/gtest.h>
#include "../src/Utils.h"
#include "SFML/System/Vector2.hpp"

const float STD_TOLERANCE = 0.001f;

TEST(utils_tests, normalize2f_always_1_magnitude) {
    for (int i = 0; i < 10; i++) {
        ASSERT_NEAR(utils::magnitude2f(utils::normalize2f(sf::Vector2f(rand()/7.f, rand()/7.f))), 1.f, STD_TOLERANCE);
    }
}

TEST(utils_tests, magnitude2f_good_for_known_vecs) {
    ASSERT_NEAR(utils::magnitude2f(sf::Vector2f(2,0)),2.f, STD_TOLERANCE);
    ASSERT_NEAR(utils::magnitude2f(sf::Vector2f(420,180)),60 * std::sqrt(58), STD_TOLERANCE);
    ASSERT_NEAR(utils::magnitude2f(sf::Vector2f(875.5,107.5)), 882.075, STD_TOLERANCE);

    ASSERT_NEAR(utils::magnitude2f(sf::Vector2f(-15.f,-3.f)), 3 * std::sqrt(26), STD_TOLERANCE);
    ASSERT_NEAR(utils::magnitude2f(sf::Vector2f(0,0)), 0, STD_TOLERANCE);
}