#pragma once

#include <vector>
#include "GridEntity.hpp"
#include "Coordinate.hpp"

class GameState;

class Command {
public:
    GameState* gameState;
    virtual ~Command() = default;
    virtual bool execute() = 0;
    virtual Command* getCommand();
};

class StateCommand : public Command {
public:
    virtual void rewind() = 0;
};

class CompositeStateCommand : public StateCommand {
public:
    std::vector<StateCommand*> commands = std::vector<StateCommand*>();
    void addCommand(StateCommand* command);
    bool execute() override;
    void rewind() override;
};

class RemoveEntityCommand : public StateCommand {
    Coordinate remove;
    GridEntity entity;

public:
    RemoveEntityCommand(const Coordinate& add, GridEntity& entity);
    bool execute() override;
    void rewind() override;
};

class AddEntityCommand : public StateCommand {
    Coordinate add;
    GridEntity entity;

public:
    AddEntityCommand(const Coordinate& remove, GridEntity& entity);
    bool execute() override;
    void rewind() override;
};

class ModelPropertyChangeCommand : public StateCommand {
    int propertyIndex;
    int propertyValueOld;
    int propertyValueNew;

public:
    ModelPropertyChangeCommand(int propertyIndex, int propertyValue);
    bool execute() override;
    void rewind() override;
};

class GeneratorCommand : public Command {
private:
    StateCommand* generatedCommand;

public:
    Command* getCommand() override;
};
