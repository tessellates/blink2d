#pragma once

#include "Command.hpp"
#include "GridEntity.hpp"

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
    std::vector<Cycle> gameCycles = std::vector<Cycle>();
    Cycle activeCycle = Cycle();


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

    void addEntity(const Coordinate& cor, const GridEntity& ent)
    {
        auto add = Command([cor, ent, this](){this->fireAddEntity(cor, ent);}, [cor, ent, this](){this->fireRemoveEntity(cor, ent);});
        add.execute();
        activeCycle.addCommand(add);
    }

    void removeEntity(const Coordinate& cor, const GridEntity& ent)
    {
        auto remove = Command([cor, ent, this](){this->fireRemoveEntity(cor, ent);}, [cor, ent, this](){this->fireAddEntity(cor, ent);});
        remove.execute();
        activeCycle.addCommand(remove);
    }
};