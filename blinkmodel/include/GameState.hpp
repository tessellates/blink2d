#pragma once

#include "Command.hpp"
#include "GridEntity.hpp"
#include <vector>

class GameStateListener {
public:
    virtual ~GameStateListener() = default;
    virtual void onAddEntity(const Coordinate& cor, const GridEntity& ent) = 0;
    virtual void onRemoveEntity(const Coordinate& cor, const GridEntity& ent) = 0;
    virtual void onModelPropertyChange(int propertyIndex, int propertyValue) = 0;
};

class GameState {
public:
    std::vector<GameStateListener*> listeners;
    std::vector<int> intProperties;
    std::vector<Cycle> gameCycles;
    Cycle activeCycle;
    int activeIndex;

    GameState();

    virtual void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent);
    virtual void fireAddEntity(const Coordinate& cor, const GridEntity& ent);
    virtual void fireModelPropertyChange(int propertyIndex, int propertyValue);

    void addEntity(const Coordinate& cor, const GridEntity& ent);
    void changeProperty(int propertyIndex, int propertyValue);
    void removeEntity(const Coordinate& cor, const GridEntity& ent);

    void saveCycle();
    void backward();
    void forward();
};
