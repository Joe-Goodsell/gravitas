cmake_minimum_required(VERSION 3.16)
project(gravitas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SOURCE_FILES 
    src/main.cpp 
    src/Particle.cpp 
    src/Utils.cpp 
    src/GravitySource.cpp
)
set(TEST_FILES 
    tests/particle_tests.cpp
    tests/example_tests.cpp
)

# BUILD PROJECT
add_executable(gravitas ${SOURCE_FILES})
target_link_libraries(gravitas PRIVATE 
    sfml-graphics
    gtest
    gtest_main
)

# BUILD TESTS
enable_testing()
# add_executable(example_tests tests/example_tests.cpp)
# add_executable(particle_tests src/Particle.cpp tests/particle_tests.cpp src/Utils.cpp)
add_executable(utils_tests tests/utils_tests.cpp src/Utils.cpp)
# target_link_libraries(example_tests PUBLIC
#     sfml-graphics
#     gtest
#     gtest_main
# )
# target_link_libraries(particle_tests PUBLIC
#     sfml-graphics
#     gtest
#     gtest_main
# )
target_link_libraries(utils_tests PUBLIC
    sfml-graphics
    gtest
    gtest_main
)
include(googletest)
# gtest_discover_tests(particle_tests utils_tests)

# add_test(NAME example_tests COMMAND example_tests)
# add_test(NAME particle_tests COMMAND particle_tests)
add_test(NAME utils_tests COMMAND utils_tests)

target_compile_features(gravitas PRIVATE cxx_std_17)

install(TARGETS gravitas)
