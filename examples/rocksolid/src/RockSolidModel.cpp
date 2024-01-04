#include "RockSolidModel.hpp"
#include "Command.hpp"
#include <algorithm> // For std::find
#include <random>


int RockSolidModel::height() const
{
    if (width() > 0)
        return nodeGrid[0].size();
    else
        return 0;
}

int RockSolidModel::width() const
{
    return nodeGrid.size();
}

bool RockSolidModel::inModel(const Coordinate& position) const
{
    if (position.x < 0 || position.x >= width())
    {
        return false;
    }
    if (position.y < 0 || position.x >= height())
    {
        return false;
    }
    return true;
}

RockSolidNode& RockSolidModel::getNode(const Coordinate& position)
{
    return nodeGrid[position.x][position.y];
}

const RockSolidNode& RockSolidModel::getNode(const Coordinate& position) const
{
    return nodeGrid[position.x][position.y];
}


void RockSolidModel::placeNodeAtPosition(const Coordinate& position, RockSolidNodeType type)
{
    if (!canPlaceNodeAtPosition(position, type))
        return;

    replaceEntity(position, getNode(position).entity(position), GridEntity(position, type));
    saveCycle();
}

void RockSolidModel::fireReplaceEntity(const Coordinate& position, const GridEntity& replaced, const GridEntity& added) 
{
    getNode(position).change(static_cast<RockSolidNodeType>(added.type));
    GameState::fireReplaceEntity(position, replaced, added);
}

void RockSolidModel::fireAddEntity(const Coordinate& position, const GridEntity& ent) 
{
    nodeGrid[position.x][position.y] = RockSolidNode(ent);
    GameState::fireAddEntity(position, ent);
}

void RockSolidModel::fireRemoveEntity(const Coordinate& position, const GridEntity& ent) 
{
    nodeGrid[position.x][position.y] = RockSolidNode(EMPTY, 0);
    GameState::fireRemoveEntity(position, ent);
}

bool RockSolidModel::canPlaceNodeAtPosition(const Coordinate& position, RockSolidNodeType type) const
{
    return true;
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
    }}

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

}

void RockSolidModel::loadLevel(const RockSolidLevel& level)
{

    int x = 0;
    int y = 0;
    int total = 0;

    nodeGrid.resize(level.layoutNodes.size());
    for (size_t i = 0; i < level.layoutNodes.size(); ++i) {
        nodeGrid[i].resize(level.layoutNodes[i].size(), RockSolidNode{EMPTY, 0});
    }

    for (const auto& nodeRows : level.layoutNodes)
    {
        for (const auto& layoutNode : nodeRows)
        {
            Coordinate position{x, y};
            GridEntity entity{position, layoutNode.type};
            entity.properties.push_back(layoutNode.gemCount);
            this->addEntity(position, entity);
            x++;
            total++;
        }
        y++;
        x = 0;
    }

    gemTarget = level.gemTarget;
    playerMoney = level.budget;
}

