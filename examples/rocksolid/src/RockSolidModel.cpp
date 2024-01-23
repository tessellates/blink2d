#include "RockSolidModel.hpp"
#include "Command.hpp"
#include <algorithm> // For std::find
#include <random>


bool RockSolidModel::inModel(const Coordinate& position) const
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

RockSolidNode& RockSolidModel::getNode(const Coordinate& position)
{
    return nodeGrid[position.x + width * position.y];
}

const RockSolidNode& RockSolidModel::getNode(const Coordinate& position) const
{
    return nodeGrid[position.x + width * position.y];
}


void RockSolidModel::placeNodeAtPosition(const Coordinate& position, RockSolidNodeType type)
{
    if (!canPlaceNodeAtPosition(position, type))
        return;

    auto oldType = getNode(position).type;
    injectCommand(Command([position, type, this](){this->replaceNode(position, type);}, [position, oldType, this](){this->replaceNode(position, oldType);}));
    saveCycle();
}

void RockSolidModel::replaceNode(const Coordinate& position, RockSolidNodeType type)
{
    getNode(position).change(type);
    for (auto& emit : replaceEmissions)
    {
        emit(position, type);
    }
}

bool RockSolidModel::canPlaceNodeAtPosition(const Coordinate& position, RockSolidNodeType type) const
{
    if (!(getNode(position).canPlace | type))
        return false;
    
    if (RockSolidNode::needsGround | type)
    {
        auto down = position.getNeighbor(DOWN);
        if (!inModel(down))
            return false;
        if (!(getNode(down).type | RockSolidNode::isGround))
            return false;
    }
    if (RockSolidNode::needsVertical | type)
    {
        auto down = position.getNeighbor(DOWN);
        if (!inModel(down))
            return false;
        if (!(getNode(down).type | RockSolidNode::isVertical))
            return false;
    }
    if ((type | CONSTRUCT_B))
    {
        auto right = position.getNeighbor(RIGHT);
        if (!inModel(right))
            return false;
        if (!(getNode(right).type | RockSolidNode::isGround))
            return false;
    }
    if ((type | CONSTRUCT_C))
    {
        auto left = position.getNeighbor(LEFT);
        if (!inModel(left))
            return false;
        if (!(getNode(left).type | RockSolidNode::isGround))
            return false;
    }
    return true;
}

float RockSolidModel::demolitionCost(const Coordinate& position) const
{
    switch (getNode(position).demolitionThreshold) 
    {
        case SOFT:
            return 30;
        case HARD:
            return 60;
        case INDESTRUCTABLE:
            return -1;
        default:
            std::cout << "Unknown demolition threshold." << std::endl;
            return -1;
    }
}

float RockSolidModel::placeCost(const Coordinate& position, RockSolidNodeType type) const
{
    if (!canPlaceNodeAtPosition(position, type))
    {
        return -1;
    }
    return nodeCosts.at(type);
}

float RockSolidModel::typeCost(RockSolidNodeType type) const
{
    return nodeCosts.at(type);
}

void RockSolidModel::nextTick()
{
    for (int x = 0; x < width: ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            auto& node.onGameTick(this, {x, y});
        }
    }
    triggerBuffer();
}

void RockSolidModel::transferGems(const Coordinate& from, const Coordinate& to)
{
    getNode(from).gemCount -= gemPerTick;
    {
        for (auto& emit : gemEmissions)
        {
            emit(position, to, +1);
        }
    }
    getNode(to).gemCount += gemPerTick;
}

void RockSolidModel::changeDirection(const Coordinate& target, const Direction& direction)
{
    if (getNode(target).direction == direction)
    {
        return;
    }

    getNode(target).direction = direction;
    for (auto& emit : directionEmissions)
    {
        emit(target, direction);
    }
}

void RockSolidModel::loadLevel(const RockSolidLevel& level)
{
    int x = 0;
    int y = 0;
    width = level.width;
    height = level.header;
    nodeGrid = {level.layoutNodes.size(), {}};
    for (const auto& layoutNode : level.layoutNodes)
    {
        Coordinate position{x, y};
        replaceNode({x, y}, layoutNode.type);
        getNode({x, y}).gemCount = layoutNode.gemCount;
        x++;
        if (x => width)
        {
            y++;
            x = 0;
        }
    }
    gemTarget = level.gemTarget;
    playerMoney = level.budget;
}

