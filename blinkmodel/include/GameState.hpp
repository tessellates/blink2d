#pragma once

#include "Command.hpp"
#include "GridEntity.hpp"
#include <vector>

class GameStateListener {
public:
    virtual ~GameStateListener() = default;
    virtual void onAddEntity(const Coordinate& cor, const GridEntity& ent) {};
    virtual void onRemoveEntity(const Coordinate& cor, const GridEntity& ent) {};
    virtual void onModelPropertyChange(int propertyIndex, int propertyValue) {};
    virtual void onReplaceEntity(const Coordinate& cor, const GridEntity& replaced, const GridEntity& added) {};
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
    virtual void fireReplaceEntity(const Coordinate& cor, const GridEntity& replaced, const GridEntity& added);

    void addEntity(const Coordinate& cor, const GridEntity& ent);
    void changeProperty(int propertyIndex, int propertyValue);
    void removeEntity(const Coordinate& cor, const GridEntity& ent);
    void replaceEntity(const Coordinate& cor, const GridEntity& replaced, const GridEntity& added);

    void saveCycle();
    void backward();
    void forward();
};
