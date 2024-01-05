
#include "RockSolidNode.hpp"
#include "RockSolidModel.hpp"

std::unordered_map<RockSolidNodeType, std::function<void(RockSolidNode&)>> RockSolidNode::initMap = {
    {EMPTY, &RockSolidNode::initializeEmpty},
    {DIRT, &RockSolidNode::initializeDirt},
    {ROCK, &RockSolidNode::initializeRock},
    {GEM_DEPOSIT, &RockSolidNode::initializeGemDeposit},
    {EXIT, &RockSolidNode::initializeExit},
    {HORIZONTAL_EXTRACTOR, &RockSolidNode::initializeHorizontalExtractor},
    {VERTICAL_EXTRACTOR, &RockSolidNode::initializeVerticalExtractor},
    {HORIZONTAL_BELT, &RockSolidNode::initializeHorizontalBelt},
    {VERTICAL_BELT, &RockSolidNode::initializeVerticalBelt},
    {HORIZONTAL_ENGINE, &RockSolidNode::initializeHorizontalEngine},
    {VERTICAL_ENGINE, &RockSolidNode::initializeVerticalEngine},
    {CONSTRUCT_A, &RockSolidNode::initializeConstructA},
    {CONSTRUCT_B, &RockSolidNode::initializeConstructB},
    {CONSTRUCT_C, &RockSolidNode::initializeConstructC},
    {BEDROCK, &RockSolidNode::initializeBedrock}
};

RockSolidNode::RockSolidNode(RockSolidNodeType type, int gemCount) : type(type), gemCount(gemCount) 
{
    if (type == 0)
    {
        change(EMPTY);
    }
    else
    {
        change(type);
    }
}

RockSolidNode::RockSolidNode(const GridEntity& entity) : RockSolidNode(static_cast<RockSolidNodeType>(entity.type), entity.properties[GEM_COUNT])
{

}

GridEntity RockSolidNode::entity(const Coordinate& position) const
{
    GridEntity ent{position, type};
    ent.properties.push_back(gemCount);
    return ent;
}

void RockSolidNode::change(RockSolidNodeType type)
{
    this->canPlace = 0; // default
    auto it = initMap.find(type);
    if (it != initMap.end()) 
    {
        it->second(*this);
    } else {
        std::cout <<type<<std::endl;
        throw std::invalid_argument("Invalid RockSolidNodeType");
    }
}

void RockSolidNode::onGameTick()
{
    if (gameTickBehaviour != nullptr)
        (*gameTickBehaviour)(*this);
}


void RockSolidNode::initializeEmpty(RockSolidNode& node) {
    node.canPlace = (1 << 14) - 1 - (1 << 5) - (1 << 6);
}

void RockSolidNode::initializeDirt(RockSolidNode& node) {

}

void RockSolidNode::initializeRock(RockSolidNode& node) {
    // Specific initialization logic for rock
}

void RockSolidNode::initializeGemDeposit(RockSolidNode& node) {
    node.canPlace = (1 << 5) + (1 << 6);
}

void RockSolidNode::initializeExit(RockSolidNode& node) {
    // Specific initialization logic for exit
}

void RockSolidNode::initializeHorizontalExtractor(RockSolidNode& node) {
    // Specific initialization logic for horizontal extractor
}

void RockSolidNode::initializeVerticalExtractor(RockSolidNode& node) {
    // Specific initialization logic for vertical extractor
}

void RockSolidNode::initializeHorizontalBelt(RockSolidNode& node) {
    // Specific initialization logic for horizontal belt
}

void RockSolidNode::initializeVerticalBelt(RockSolidNode& node) {
    // Specific initialization logic for vertical belt
}

void RockSolidNode::initializeHorizontalEngine(RockSolidNode& node) {
    // Specific initialization logic for horizontal engine
}

void RockSolidNode::initializeVerticalEngine(RockSolidNode& node) {
    // Specific initialization logic for vertical engine
}

void RockSolidNode::initializeConstructA(RockSolidNode& node) {
    // Specific initialization logic for construct A
}

void RockSolidNode::initializeConstructB(RockSolidNode& node) {
    // Specific initialization logic for construct B
}

void RockSolidNode::initializeConstructC(RockSolidNode& node) {
    // Specific initialization logic for construct C
}

void RockSolidNode::initializeBedrock(RockSolidNode& node) {
    // Specific initialization logic for bedrock
}

//int needsGround = (EMPTY | DIRT | ROCK |GEM_DEPOSIT |EXIT |HORIZONTAL_EXTRACTOR |VERTICAL_EXTRACTOR |HORIZONTAL_BELT |VERTICAL_BELT |HORIZONTAL_ENGINE |VERTICAL_ENGINE |CONSTRUCT_A | CONSTRUCT_B | CONSTRUCT_C | BEDROCK)

int RockSolidNode::isGround  = (DIRT | ROCK |GEM_DEPOSIT | CONSTRUCT_A | CONSTRUCT_B | CONSTRUCT_C | BEDROCK);
int RockSolidNode::needsGround = (HORIZONTAL_BELT | HORIZONTAL_ENGINE | CONSTRUCT_A);

int RockSolidNode::isVertical = (VERTICAL_BELT | VERTICAL_ENGINE | VERTICAL_EXTRACTOR);
int RockSolidNode::needsVertical = (VERTICAL_BELT | VERTICAL_ENGINE);
