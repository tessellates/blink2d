#pragma once

#include <Coordinate.hpp>
#include <Command.hpp>
#include <Direction.hpp>
#include <random>
#include <GameState.hpp>
#include <deque>

enum SnakeModelProperties
{
    DIRECTION
};

class SnakeModel : public GameState
{
public:
    int width;
    int height;
    std::deque<Coordinate> snake;
    Coordinate food;

    SnakeModel() = default;

    SnakeModel(int width, int height) : width(width), height(height)
    {
        snake = std::deque<Coordinate>();
        intProperties.push_back(Direction::UP);
    };


    void start()
    {
        //moveHead(randomCoordinate());
        //spawnFood();
    }

    bool changeDirection(Direction direction)
    {
        if (snake.size() == 1)
        {
            intProperties[DIRECTION] = direction;
            return true;
        }
        auto c = snake.front().getNeighbor(direction);
        if (std::find(snake.cbegin(), snake.cbegin()+2, c) == snake.cbegin()+2)
        {
            intProperties[DIRECTION] = direction;
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

    void moveHead(const Coordinate& pos)
    {
        auto ent = GridEntity(pos);
        ent.type = 0;
        addEntity(pos, ent);
    }

    void spawnFood()
    {
        if (snake.size() == width*height)
        {
            winGame();
            return;
        }
        Coordinate foodcoor = randomCoordinate();
        while (std::find(snake.cbegin(), snake.cend(), foodcoor) != snake.cend())
        {
            foodcoor = randomCoordinate();
        }
        auto ent = GridEntity(foodcoor);
        ent.type = 1;
        addEntity(foodcoor, ent);
        return;
    }

    void spawn(const Coordinate& pos)
    {
        moveHead(pos);

        if (pos != food)
        {
            if (snake.size() > 1)
            {
                auto ent = GridEntity(snake.back());
                removeEntity(snake.back(), ent);
            }
            else
            {
                return;
            }
        }            
        else
        {
            spawnFood();
        }
    }

    bool nextStep()
    {
        if (snake.size() == 0 )
        {

            moveHead(randomCoordinate());
            spawnFood();
            return true;
        }
        auto destination = snake.front().getNeighbor(intProperties[DIRECTION]);
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
        spawn(destination);
        return true;
    }


    void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) override
    {
        snake.pop_back();
        GameState::fireRemoveEntity(cor, ent);
    }

    void fireAddEntity(const Coordinate& cor, const GridEntity& ent) override
    {
        if (ent.type == 0)
            snake.push_front(cor);
        else
            food = cor;
        GameState::fireAddEntity(cor, ent);
    }

    bool inBounds(const Coordinate& position)
    {
        if (position.x < 0 || position.x >= width)
            return false;
        if (position.y < 0 || position.y >= height)
            return false;
        return true;
    }

    void loseGame()
    {
    }

    void winGame()
    {
    }
};
