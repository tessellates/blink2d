#pragma once

class GameManager
{
public:
    // Get the instance of the GameManager
    static GameManager* getInstance();

    // Delete copy constructor and assignment operator for Singleton
    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    // Game related functions can go here...
    void initialize();
    void update();
    void shutdown();

private:
    static GameManager* singleton_; 
    GameManager();
    ~GameManager();   

    // Add any member variables required by the game manager here...
};

