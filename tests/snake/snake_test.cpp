// main_tests.cpp
#include <gtest/gtest.h>
#include <SnakeModel.hpp>
#include <Command.hpp>

TEST(SnakeModel, Constructor) {
    SnakeModel snakeModel{};
}

TEST(SnakeModel, nextStep) {
    SnakeModel snakeModel{8, 8};
    CompositeStateCommand gameCycle = CompositeStateCommand();
    snakeModel.nextStep(gameCycle);
}


// Main function that runs the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
