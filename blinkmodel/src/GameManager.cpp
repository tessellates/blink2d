#include "GameManager.hpp"

// Get the instance of the GameManager
GameManager& GameManager::getInstance()
{
    /**
        * This is a safer way to create an instance. instance = new Singleton is
        * dangerous in case two instance threads wants to access at the same time
        */
    if(singleton_ == nullptr)
    {
        singleton_ = new GameManager();
    }
    return singleton_;
}

void GameManager::initialize()
{
    // Initialization code...
}

void GameManager::update()
{
    // Game update code...
}

void GameManager::shutdown()
{
    // Cleanup code...
}
