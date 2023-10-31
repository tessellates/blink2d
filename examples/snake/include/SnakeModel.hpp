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

    AddEntityCommand* moveHead(const Coordinate& pos)
    {
        auto ent = GridEntity(pos);
        ent.type = 0;
        AddEntityCommand* moveHead = new AddEntityCommand(pos, ent);
        moveHead->gameState = this;
        return moveHead;
    }

    AddEntityCommand* spawnFood()
    {
        if (snake.size() == width*height)
        {
            winGame();
            return nullptr;
        }
        Coordinate foodcoor = randomCoordinate();
        while (std::find(snake.cbegin(), snake.cend(), foodcoor) != snake.cend())
        {
            foodcoor = randomCoordinate();
        }
        auto ent = GridEntity(foodcoor);
        ent.type = 1;
        AddEntityCommand* command = new AddEntityCommand(foodcoor, ent);
        command->gameState = this;
        return command;
    }

    void spawn(CompositeStateCommand& gameCycle, const Coordinate& pos)
    {
        auto ent = GridEntity(pos);
        ent.type = 0;
        AddEntityCommand* moveHeadCommand = moveHead(pos);
        moveHeadCommand->execute();
        gameCycle.addCommand(moveHeadCommand);

        if (pos != food)
        {
            if (snake.size() > 1)
            {
                ent = GridEntity(snake.back());
                RemoveEntityCommand* removeTail = new RemoveEntityCommand(snake.back(), ent);
                removeTail->gameState = this;
                removeTail->execute();
                gameCycle.addCommand(removeTail);
            }
            else
            {
                return;
            }
        }            
        else
        {
            AddEntityCommand* spawnF = spawnFood();
            if (spawnF)
            {
                spawnF->execute();
                gameCycle.addCommand(spawnF);
            }
        }
    }

    bool nextStep(CompositeStateCommand& gameCycle)
    {
        if (snake.size() == 0 )
        {
            AddEntityCommand* moveHeadCommand = moveHead(randomCoordinate());
            moveHeadCommand->execute();
            gameCycle.addCommand(moveHeadCommand);
            AddEntityCommand* spawnF = spawnFood();
            if (spawnF)
            {
                spawnF->execute();
                gameCycle.addCommand(spawnF);
            }
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
        spawn(gameCycle, destination);
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
