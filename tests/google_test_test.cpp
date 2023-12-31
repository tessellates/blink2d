// main_tests.cpp
#include <gtest/gtest.h>
#include <Coordinate.hpp>

// A function that we will test
int add(int a, int b) {
    return a + b;
}

// Tests directly in the same file
TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(1, 1), 2);
    EXPECT_EQ(add(10, 14), 24);
    EXPECT_EQ(add(100, 200), 300);
}

TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(add(-1, -1), -2);
    EXPECT_EQ(add(-10, -14), -24);
}

TEST(AdditionTest, MixedNumbers) {
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(10, -14), -4);
}

TEST(CoordinateTest, Coordinates) {
    Coordinate c = Coordinate(5, 6);
    Coordinate c2 = Coordinate(5, 6);
    EXPECT_EQ(c, c2);

}


// Main function that runs the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
