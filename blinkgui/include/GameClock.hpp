#pragma once
#include <SDL.h>

class GameClock {
public:
    GameClock(float gameSpeed);
    void update(); // Call this once per frame
    void reset(); 
    float getDeltaTime() const; // Get the time elapsed since last frame in seconds
    float getIntervalTime() const; // Get the time elapsed since last frame in seconds
    float getIntervalProgress() const; 
    float getProgress() const;
    void setGameSpeed(float gameSpeed); // Get the time elapsed since last frame in seconds
    float getGameSpeed() const; // Get the time elapsed since last frame in seconds
    Uint32 getTotalTime() const; // Get the total elapsed time since the start of the clock in milliseconds

private:
    Uint32 lastTick; // Time of the last update call
    Uint32 startTick; // The time when the clock was started
    Uint32 intervalTick; // The time when the clock was started
    float gameSpeed; // The time when the clock was started
    float deltaTime; // Time between the current frame and the last frame in seconds
    float intervalTime;// Time between
};
