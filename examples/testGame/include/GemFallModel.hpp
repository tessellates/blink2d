#pragma once

#include "Coordinate.hpp"
#include <stack>
#include "CommandHistory.hpp"
#include "Direction.hpp"
#include <optional>

enum FallPieceType
{
    NONE_FALL_PIECE,
    GEMS,
    SPAWNER
};

struct FallPiece
{
    FallPieceType type;
    int gems;
    bool gemsThisTick = false;
};

class GemFallModel : public CommandHistory
{
public:
    GemFallModel();
    GemFallModel(int);

    void add(const Coordinate& position);
    void remove(const Coordinate& position);
    void play(const Coordinate& position);

    FallPiece& getNode(const Coordinate& position);
    void changeGems(const Coordinate& position, int);

    bool inModel(const Coordinate& position) const;

    void tick();

public:
    std::vector<std::function<void(const Coordinate&)>> addGem;
    std::vector<std::function<void(const Coordinate&)>> removePiece;
    std::vector<std::function<void(const Coordinate&)>> addSpawn;
    std::vector<std::function<void(const Coordinate&)>> permGem;

    int height;
    int width;

    std::vector<FallPiece> board;
    
};
