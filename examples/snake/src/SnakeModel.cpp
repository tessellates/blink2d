#include "SnakeModel.hpp"
#include "Command.hpp"
#include <algorithm> // For std::find
#include <random>

// Constructors
SnakeModel::SnakeModel() : width(0), height(0), isFood(false) {
    // Body intentionally empty
}

SnakeModel::SnakeModel(int width, int height) : width(width), height(height), isFood(false) {
    snake = std::deque<Coordinate>();
    intProperties.push_back(Direction::UP);
}

// Member Functions
void SnakeModel::start() {
    // moveHead(randomCoordinate());
    // spawnFood();
}

bool SnakeModel::changeDirection(Direction direction) {
    if (snake.size() <= 1) {
        changeProperty(DIRECTION, direction);
        return true;
    }
    auto c = snake.front().getNeighbor(direction);
    if (std::find(snake.cbegin(), snake.cbegin() + 2, c) == snake.cbegin() + 2) {
        changeProperty(DIRECTION, direction);
        return true;
    }
    return false;
}

Coordinate SnakeModel::randomCoordinate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(0, width - 1);
    std::uniform_int_distribution<> yDist(0, height - 1);
    return Coordinate(xDist(gen), yDist(gen));
}

void SnakeModel::moveHead(const Coordinate& pos) {
    GridEntity ent(pos);
    ent.type = 0;
    addEntity(pos, ent);
}

void SnakeModel::spawnFood() {
    if (snake.size() == width * height) {
        winGame();
        return;
    }
    Coordinate foodcoor = randomCoordinate();
    while (std::find(snake.cbegin(), snake.cend(), foodcoor) != snake.cend()) {
        foodcoor = randomCoordinate();
    }
    GridEntity ent(foodcoor);
    ent.type = 1;
    addEntity(foodcoor, ent);
}

void SnakeModel::spawn(const Coordinate& pos) {
    if (!isFood || pos != food) {
        moveHead(pos);
        if (snake.size() > 1) {
            GridEntity ent(snake.back());
            ent.type = 2;
            removeEntity(snake.back(), ent);
        }
    } else {
        if (isFood && pos == food) {
            GridEntity ent(food);
            ent.type = 1;
            removeEntity(food, ent);
            moveHead(pos);
            spawnFood();
        }
    }
}

bool SnakeModel::nextStep() {
    if (snake.empty()) {
        moveHead(randomCoordinate());
        spawnFood();
        return true;
    }
    auto destination = snake.front().getNeighbor(intProperties[DIRECTION]);
    if (!inBounds(destination)) {
        loseGame();
        return false;
    }
    if (std::find(snake.cbegin(), snake.cend(), destination) != snake.cend()) {
        loseGame();
        return false;
    }
    spawn(destination);
    saveCycle();
    return true;
}

void SnakeModel::fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) {
    if (ent.type == 2)
        snake.pop_back();
    if (ent.type == 1)
        isFood = false;
    if (ent.type == 0)
        snake.pop_front();
    GameState::fireRemoveEntity(cor, ent);
}

void SnakeModel::fireAddEntity(const Coordinate& cor, const GridEntity& ent) {
    if (ent.type == 0)
        snake.push_front(cor);
    if (ent.type == 1) {
        food = cor;
        isFood = true;
    }
    if (ent.type == 2)
        snake.push_back(cor);
    GameState::fireAddEntity(cor, ent);
}

bool SnakeModel::inBounds(const Coordinate& position) {
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < height;
}

void SnakeModel::loseGame() {
    // Implementation of loseGame
}

void SnakeModel::winGame() {
    // Implementation of winGame
}
