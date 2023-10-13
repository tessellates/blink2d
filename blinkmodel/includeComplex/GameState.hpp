#pragma once

#include <GridEntity.hpp>



#ifndef GAME_STATE_COUNT
#define GAME_STATE_COUNT 1  // Default size if not defined elsewhere
#endif

template<typename Coordinate>
class GameStateManager {
private:
    static GameState<Coordinate> gameStates[GAME_STATE_COUNT];

public:
    static GameState<Coordinate>& getGameState(size_t index) {
        if(index >= GAME_STATE_COUNT) {
            throw std::out_of_range("Index out of bounds");
        }
        return gameStates[index];
    }

    // ... other functions to manage the game states...
};

// Define the static member outside the class template definition
template<typename Coordinate>
GameState<Coordinate> GameStateManager<Coordinate>::gameStates[GAME_STATE_COUNT];


template<typename Coordinate>
class GameState {
private:
    GameGrid<Coordinate> grid;

public:
    GameState() {
        // Initialization if necessary
    }

    GameGrid<Coordinate>& getGrid() const {
        return grid;
    }

    // ... other functions for the GameState...
};