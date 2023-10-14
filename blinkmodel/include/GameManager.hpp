#pragma once

#include <Singleton.hpp>

class GameManager : public Singleton<GameManager>
{
    friend class Singleton<GameManager>; // Grant base access to constructor.
public:
    // boiler-plate singleton
    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    // Game related functions can go here...
    void initialize();
    void update();
    void shutdown();

private:
    GameManager() = default;
    ~GameManager() = default;   

    // Add any member variables required by the game manager here...
};

