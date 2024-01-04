#include "GameState.hpp"

GameState::GameState() : activeIndex(-1) {}

void GameState::fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) {
    for(auto listener : listeners) {
        listener->onRemoveEntity(cor, ent);
    }
}

void GameState::fireAddEntity(const Coordinate& cor, const GridEntity& ent) {
    for(auto listener : listeners) {
        listener->onAddEntity(cor, ent);
    }
}

void GameState::fireModelPropertyChange(int propertyIndex, int propertyValue) {
    intProperties[propertyIndex] = propertyValue;
    for(auto listener : listeners) {
        listener->onModelPropertyChange(propertyIndex, propertyValue);
    }
}

void GameState::fireReplaceEntity(const Coordinate& cor, const GridEntity& replaced, const GridEntity& added) {
    for(auto listener : listeners) {
        listener->onReplaceEntity(cor, replaced, added);
    }
}

void GameState::addEntity(const Coordinate& cor, const GridEntity& ent) {
    auto add = Command([cor, ent, this](){this->fireAddEntity(cor, ent);}, [cor, ent, this](){this->fireRemoveEntity(cor, ent);});
    add.execute();
    activeCycle.addCommand(add);
}

void GameState::changeProperty(int propertyIndex, int propertyValue) {
    int previousPropertyValue = intProperties[propertyIndex];
    auto change = Command([propertyIndex, propertyValue, this](){this->fireModelPropertyChange(propertyIndex, propertyValue);}, [propertyIndex, previousPropertyValue, this](){this->fireModelPropertyChange(propertyIndex, previousPropertyValue);});
    change.execute();
    activeCycle.addCommand(change);
}

void GameState::removeEntity(const Coordinate& cor, const GridEntity& ent) {
    auto remove = Command([cor, ent, this](){this->fireRemoveEntity(cor, ent);}, [cor, ent, this](){this->fireAddEntity(cor, ent);});
    remove.execute();
    activeCycle.addCommand(remove);
}

void GameState::replaceEntity(const Coordinate& cor, const GridEntity& replaced, const GridEntity& added) {
    auto replace = Command([cor, replaced, added, this](){this->fireReplaceEntity(cor, replaced, added);}, [cor, replaced, added, this](){this->fireReplaceEntity(cor, added, replaced);});
    replace.execute();
    activeCycle.addCommand(replace);
}


void GameState::saveCycle() {
    if (gameCycles.size() - 1 > activeIndex) {

        gameCycles.erase(gameCycles.begin() + activeIndex + 1, gameCycles.end());
    }
    gameCycles.push_back(activeCycle);
    activeCycle = Cycle();
    activeIndex++;
}

void GameState::backward() 
{
    if (activeIndex >= 0) {

        gameCycles[activeIndex].rewind();
        activeIndex--;
    }
}

void GameState::forward() {
    if (activeIndex + 1 < gameCycles.size()) {
        activeIndex++;
        gameCycles[activeIndex].execute();
    }
}
