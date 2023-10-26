#pragma once

#include "Command.hpp"

class GameStateListener
{
public:
    virtual void onAddEntity(const Coordinate& cor, const GridEntity& ent) = 0;
    virtual void onRemoveEntity(const Coordinate& cor, const GridEntity& ent) = 0;
    virtual void onModelPropertyChange(int propertyIndex, int propertyValue) = 0;
};

class GameState {
public:
    std::vector<GameStateListener*> listeners = std::vector<GameStateListener*>();
    std::vector<int> intProperties = std::vector<int>();
public:
    virtual void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) 
    {
        for(auto listener : listeners)
        {
            listener->onRemoveEntity(cor, ent);
        }
    }

    virtual void fireAddEntity(const Coordinate& cor, const GridEntity& ent) 
    {
        for(auto listener : listeners)
        {
            listener->onAddEntity(cor, ent);
        }
    }

    virtual void fireModelPropertyChange(int propertyIndex, int propertyValue) 
    {
        for(auto listener : listeners)
        {
            listener->onModelPropertyChange(propertyIndex, propertyValue);
        }
    }
};