#include "Command.hpp"
#include "GameState.hpp"

// For Command class
Command* Command::getCommand() {
    return this;
}

// For CompositeStateCommand class
bool CompositeStateCommand::execute() {
    // Iterating forward and executing each command in the composite
    for(auto it = commands.begin(); it != commands.end(); ++it) {
        (*it)->execute();
    }
    return true; // Assuming the method should return true on successful execution
}

void CompositeStateCommand::rewind() {
    // Iterating backward and rewinding each command in the composite
    for(auto it = commands.rbegin(); it != commands.rend(); ++it) {
        (*it)->rewind();
    }
}

void CompositeStateCommand::addCommand(StateCommand* command)
{
    commands.push_back(command);
}
// For RemoveEntityCommand class
RemoveEntityCommand::RemoveEntityCommand(const Coordinate& remove, GridEntity& entity) 
    : remove(remove), entity(entity) {
    // Constructor implementation if necessary
}

bool RemoveEntityCommand::execute() {
    gameState->fireRemoveEntity(remove, entity);
    return true; // or your appropriate return value
}

void RemoveEntityCommand::rewind() {
    gameState->fireAddEntity(remove, entity);
}

// For AddEntityCommand class
AddEntityCommand::AddEntityCommand(const Coordinate& add, GridEntity& entity) 
    : add(add), entity(entity) {
    // Constructor implementation if necessary
}

bool AddEntityCommand::execute() {
    gameState->fireAddEntity(add, entity);
    // Implementation of execute
    return true; // or your appropriate return value
}

void AddEntityCommand::rewind() {
    gameState->fireRemoveEntity(add, entity);
}

// For ModelPropertyChangeCommand class
ModelPropertyChangeCommand::ModelPropertyChangeCommand(int propertyIndex, int propertyValue) : propertyIndex(propertyIndex), propertyValueOld(gameState->intProperties[propertyIndex]), propertyValueNew(propertyValue) {}

bool ModelPropertyChangeCommand::execute() {
    gameState->fireModelPropertyChange(propertyIndex, propertyValueNew);
    // Implementation of execute
    return true; // or your appropriate return value
}

void ModelPropertyChangeCommand::rewind() {
    gameState->fireModelPropertyChange(propertyIndex, propertyValueOld);
}



// For GeneratorCommand class
Command* GeneratorCommand::getCommand() {
    return generatedCommand; // or your appropriate logic
}
