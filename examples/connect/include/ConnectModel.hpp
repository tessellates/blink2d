#pragma once

#include <Coordinate.hpp> // This should be a user-defined header file.
#include <queue>
#include "GameState.hpp"
#include "Direction.hpp"
#include <optional>

// Forward declaration of classes used in the header
enum ConnectProperties
{
    PLAYER,
    END
};

// Forward declaration of classes used in the header
class ConnectModel : public GameState
{
public:
    ConnectModel();
    void play(int column);
    void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireAddEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireWin();
    std::optional<std::vector<Coordinate>> checkWin(const std::vector<std::queue<int>>& board, int player);

public:
    std::vector<std::queue<int>> board;
    std::optional<std::vector<Coordinate>> win;
};
