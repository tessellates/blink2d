#include "ConnectModel.hpp"
#include "Command.hpp"
#include <algorithm> // For std::find
#include <random>

// Constructors
ConnectModel::ConnectModel()
{
    intProperties.push_back(0);
    board = std::vector<std::queue<int>>(7);
}

void ConnectModel::fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) {
    board[cor.x].pop();
    GameState::fireRemoveEntity(cor, ent);
}

void ConnectModel::fireAddEntity(const Coordinate& cor, const GridEntity& ent) {
    board[cor.x].push(intProperties[ConnectProperties::PLAYER]);
    GameState::fireAddEntity(cor, ent);
}

void ConnectModel::play(int column)
{
    assert(column < 7);
    if (board[column].size() >= 6)
    {
        return;
    }
    Coordinate pos = Coordinate(column, 6 - board[column].size());
    GridEntity ent = GridEntity(pos, intProperties[ConnectProperties::PLAYER]);
    addEntity(pos, ent);
    changeProperty(0, !intProperties[ConnectProperties::PLAYER]);
    saveCycle();
}