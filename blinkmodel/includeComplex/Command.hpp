#pragma once

#include <GridEntity.hpp>
#include <GameState.hpp>

template<typename Coordinate, typename _DerivedCommand>
class Command : public CRTP<_DerivedCommand> {
public:
    Command(GameState& sta): state(sta){};
    bool execute()
    {
        return derived.execute();
    };
    bool undo()
    {
        return derived.undo();
    };
};


template<typename Coordinate>
class ChangeEntityTypeCommand : public Command {
private:
    GridEntity<Coordinate>& entity;
    EntityType newType;
    EntityType oldType;

public:
    ChangeEntityTypeCommand(GridEntity<Coordinate>& ent, EntityType newT, GameState& sta)
        : Command(sta), entity(ent), newType(newT), oldType(ent.type) {}

    bool execute() override {
        entity.type = newType;
        return true;
    };

    bool undo() {
        entity.type = oldType;
        return true;
    };
};

template<typename Coordinate>
class MoveEntityCommand : public Command {
private:
    GridEntity<Coordinate>& entity;
    Coordinate newPos;
    Coordinate oldPos;

public:
    ChangeEntityTypeCommand(GridEntity<Coordinate>& ent, Coordinate newP, GameState& sta)
        : Command(sta), entity(ent), newPos(newP), oldType(ent.position) {}

    bool execute() override {

        if (false)
        {
            return false;
        }
        
        entity.position = newPos;  // Store the old type for possible undo operations
        entity.type = newType;
        return true;
    }

    bool undo() {
        entity.type = oldType;
        return true;
    }
};


template<typename Coordinate>
class ChangePropertyCommand : public Command {
private:
    GridEntity<Coordinate>& entity;
    Property property;
    int oldValue;
    int newValue;

public:
    ChangeEntityTypeCommand(GridEntity<Coordinate>& ent, Property pr, int newV, GameState& sta)
        : Command(sta), entity(ent), property(pr), oldValue(ent.Properties[pr]), newValue(newV) {}

    bool execute() override {
        entity.type = newType;
        return true;
    };

    bool undo() {
        entity.type = oldType;
        return true;
    };
};