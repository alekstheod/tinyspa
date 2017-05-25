project(NeuralNetwork_ut)
cmake_minimum_required(VERSION 2.8)

enable_testing()
add_executable(spa_ut test.cpp)
add_test(NAME spa_ut COMMAND spa_ut)

target_include_directories(spa_ut  PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET spa_ut
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure)