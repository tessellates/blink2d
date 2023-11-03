#pragma once

#include <Coordinate.hpp> // This should be a user-defined header file.
#include <deque>
#include "GameState.hpp"
#include "Direction.hpp"

// Forward declaration of classes used in the header
enum SnakeModelProperties
{
    DIRECTION
};

class SnakeModel : public GameState
{
public:
    SnakeModel();
    SnakeModel(int width, int height);

    void start();
    bool changeDirection(Direction direction);
    Coordinate randomCoordinate();
    void moveHead(const Coordinate& pos);
    void spawnFood();
    void spawn(const Coordinate& pos);
    bool nextStep();

    void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireAddEntity(const Coordinate& cor, const GridEntity& ent) override;
    bool inBounds(const Coordinate& position);

    void loseGame();
    void winGame();

public:
    int width;
    int height;
    std::deque<Coordinate> snake;
    Coordinate food;
    bool isFood = false;
};
