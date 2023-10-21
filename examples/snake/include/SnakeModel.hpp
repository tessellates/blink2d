#pragma once

#include <Coordinate.hpp>
#include <Direction.hpp>
#include <random>
#include <deque>

class EpicModel
{
public:
    virtual void OnVictory() = 0;
    virtual void OnLose() = 0;
    virtual void OnEntityChanged(const GridEntity& entity) = 0;
    virtual void OnRemoveEntity(const Coordinate& pos) = 0;
};

class SnakeModelListener
{
public:
    virtual void OnSnakeModelUpdate() = 0;
    virtual void OnVictory() = 0;
    virtual void OnLose() = 0;
    virtual void OnSnakeModelLocationUpdate(const GridEntity& entity) = 0;
    virtual void OnRemoveEntity(const Coordinate& pos) = 0;
};

class SnakeModel
{
public:
    int width;
    int height;
    std::deque<Coordinate> snake;
    Coordinate food;
    Direction direction;
    std::vector<SnakeModelListener*> listeners;
    bool isPaused; // probably higher up

    SnakeModel() = default;
    SnakeModel(int width, int height) : width(width), height(height)
    {
        snake = std::deque<Coordinate>();
        listeners = std::vector<SnakeModelListener*>();
        direction = Direction::UP;
        isPaused = true;
    };

    void start()
    {
        moveHead(randomCoordinate());
        spawnFood();
    }

    bool changeDirection(Direction direction)
    {
        if (snake.size() == 1)
        {
            this->direction = direction;
            return true;
        }
        auto c = snake.front().getNeighbor(direction);
        if (std::find(snake.cbegin(), snake.cbegin()+2, c) == snake.cbegin()+2)
        {
            this->direction = direction;
            return true;
        }
        return false;
    }

    Coordinate randomCoordinate() {
        // Create a random device
        std::random_device rd;

        // Initialize Mersenne Twister pseudo-random number generator
        std::mt19937 gen(rd());

        // Define distribution ranges for x and y
        std::uniform_int_distribution<> xDist(0, width - 1);
        std::uniform_int_distribution<> yDist(0, height - 1);

        // Generate random x and y values
        int x = xDist(gen);
        int y = yDist(gen);

        return Coordinate(x, y);
    };

    void spawnFood()
    {
        if (snake.size() == width*height)
        {
            winGame();
            return;
        }
        food = randomCoordinate();
        while (std::find(snake.cbegin(), snake.cend(), food) != snake.cend()) 
        {
            food = randomCoordinate();
        }
        auto ent = GridEntity(food);
        ent.type = 1;
        fireSnakeModelLocationUpdate(ent);
    }

    bool nextStep()
    {
        auto destination = snake.front().getNeighbor(direction);
        if (!inBounds(destination))
        {
            loseGame();
            return false;
        }
        if (std::find(snake.cbegin(), snake.cend(), destination) != snake.cend())
        {
            loseGame();
            return false;
        }

        moveHead(destination);
        if (destination != food)
            removeTail();
        else
            spawnFood();

        return true;
    }

    void moveHead(const Coordinate& destination)
    {
        auto ent = GridEntity(destination);
        ent.type = 0;
        snake.push_front(destination);
        fireSnakeModelLocationUpdate(ent);
    }

    void removeTail()
    {
        auto c = snake.back();
        snake.pop_back();
        fireRemoveEntity(c);
    }

    bool inBounds(const Coordinate& position)
    {
        if (position.x < 0 || position.x >= width)
            return false;
        if (position.y < 0 || position.y >= height)
            return false;
        return true;
    }

    void fireLose()
    {
        for(auto listener : listeners)
        {
            listener->OnLose();
        }
    }

    void fireVictory()
    {
        for(auto listener : listeners)
        {
            listener->OnVictory();
        }
    }

    void fireSnake()
    {
        for(auto listener : listeners)
        {
            listener->OnLose();
        }
    }

    void fireSnakeModelLocationUpdate(const GridEntity& entity)
    {
        for(auto listener : listeners)
        {
            listener->OnSnakeModelLocationUpdate(entity);
        }
    }

    void fireRemoveEntity(const Coordinate& pos)
    {
        for(auto listener : listeners)
        {
            listener->OnRemoveEntity(pos);
        }
    }

    void loseGame()
    {
        isPaused = true;
        fireLose();
    }

    void winGame()
    {
        isPaused = true;
        fireVictory();
    }
};