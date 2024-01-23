#include "GemFallModel.hpp"

GemFallModel::GemFallModel() : GemFallModel(7) {}

GemFallModel::GemFallModel(int size)
    : height(size), width(size), board(size * size) {
    // Initialize the board with default FallPieces
    for (auto& piece : board) {
        piece.type = FallPieceType::NONE_FALL_PIECE; // Default type, adjust as needed
        piece.gems = 0; // Default gem count, adjust as needed
    }
}

void GemFallModel::play(const Coordinate& position) 
{
    if (getNode(position).type == FallPieceType::NONE_FALL_PIECE)
    {
        injectCommand(Command(
            [position, this]() { this->add(position); }, 
            [position, this]() { this->remove(position); }
        ));
    }
    else
    {
        injectCommand(Command(
            [position, this]() { this->remove(position); }, 
            [position, this]() { this->add(position); }
        ));
    }
    saveCycle();
}

void GemFallModel::add(const Coordinate& position)
{
    auto& node = getNode(position);
    node.type = FallPieceType::SPAWNER;
    node.gems = 100;
    for (auto& emit : addSpawn)
    {
        emit(position);
    }
}

void GemFallModel::remove(const Coordinate& position)
{
    auto& node = getNode(position);
    node.type = FallPieceType::NONE_FALL_PIECE;
    node.gems = 0;
    for (auto& emit : removePiece)
    {
        emit(position);
    }
}

FallPiece& GemFallModel::getNode(const Coordinate& position)
{
    return board[position.x + width * position.y];
}

void GemFallModel::changeGems(const Coordinate& position, int amount)
{
    auto& node = getNode(position);
    node.gems += amount;
    if (amount > 0)
    {
        node.gemsThisTick = true;
    }
}

void GemFallModel::tick() {
    int index = 0;
    for (auto& piece : board) 
    {
        piece.gemsThisTick = false;
        if (piece.gems > 0)
        {
            Coordinate position = {index % width, index / width};
            Coordinate down = position.getNeighbor(DOWN);
            if (inModel(down))
            {
                bufferCommand(Command(
                    [position, this]() { this->changeGems(position, -10); }, 
                    [position, this]() { this->changeGems(position, +10); }
                ));

                bufferCommand(Command(
                    [down, this]() { this->changeGems(down, 10); }, 
                    [down, this]() { this->changeGems(down, -10); }
                ));
            }
        }
        ++index;
    }

    triggerBuffer();
    saveCycle();
    index = 0;
    for (const auto& piece : board) 
    {
        if (piece.gemsThisTick && piece.type == NONE_FALL_PIECE)
        {
            Coordinate position = {index % width, index / width};
            for (auto& emit : addGem)
            {
                emit(position);
            }
        }
        if (piece.gems > 20 && piece.type == NONE_FALL_PIECE)
        {
            Coordinate position = {index % width, index / width};
            if (!inModel(position.getNeighbor(DOWN)))
            {
                for (auto& emit : permGem)
                {
                    emit(position);
                }
            }
        }
        ++index;
    }
}

bool GemFallModel::inModel(const Coordinate& position) const
{
    if (position.x < 0 || position.x >= width)
    {
        return false;
    }
    if (position.y < 0 || position.y >= height)
    {
        return false;
    }
    return true;
}
