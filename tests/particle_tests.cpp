#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(particle_tests, sanity) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  EXPECT_TRUE(true);
}

// TEST(particle_tests, particle_noexternal_update_correct) {
//   auto particle = Particle(sf::Vector2f(350,350), sf::Vector2f(0,0), 0.2f);
//   particle.update_position();
//   // TODO: write this test
//   ASSERT_TRUE(true);
// }