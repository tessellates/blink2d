
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

RockSolidNode::RockSolidNode() : type(EMPTY), gemCount(0) 
{
    change(EMPTY);
}

void RockSolidNode::change(RockSolidNodeType type)
{
    this->direction = NONE;
    this->canPlace = 0; // default
    gameTickBehaviour = nullptr;
    auto it = initMap.find(type);
    if (it != initMap.end()) 
    {
        it->second(*this);
    } else {
        throw std::invalid_argument("Invalid RockSolidNodeType");
    }
}

void RockSolidNode::onGameTick(RockSolidModel& model, const Coordinate& position)
{
    if (gameTickBehaviour != nullptr)
        (*gameTickBehaviour)(*this, model, position);
}


void RockSolidNode::initializeEmpty(RockSolidNode& node) {
    node.canPlace = (1 << 14) - 1 - (1 << 5) - (1 << 6);
    this->direction = DOWN;
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

void RockSolidNode::behave(RockSolidNode& node, RockSolidModel& model, const Coordinate& position)
{
    if (node.direction != NONE)
    {
        auto target = position.getNeighbor(direction);
        if (model.inModel(target) && node.gemCount > 0)
        {
            model.bufferCommand([position, target, &model](){model->transferGems(position, target);}, [position, target, &model](){model->transferGems(target, position);});
        }
    }
}

void RockSolidNode::behaveHorizontal(RockSolidNode& node, RockSolidModel& model, const Coordinate& position)
{
    auto oldDirection = node.direction;
    auto left = position.getNeighbor(LEFT);
    auto right = position.getNeighbor(RIGHT);
    if (node.direction != NONE)
    {
        if (model.inModel(left))
        {
            if (model.getNode(left).direction == node.direction || (model.getNode(target).type == HORIZONTAL_BELT || model.getNode(target).type == HORIZONTAL_ENGINE))
            {
                return;
            }
        }

        if (model.inModel(right))
        {
            if (model.getNode(right).direction == node.direction || (model.getNode(target).type == HORIZONTAL_BELT || model.getNode(target).type == HORIZONTAL_ENGINE))
            {
                return;
            }
        }

        model.bufferCommand([position, &model](){model->changeDirection(position, NONE);}, [position, oldDirection, &model](){model->changeDirection(position, oldDirection);});
        return;
    }

    if (model.inModel(left))
    {
        if (model.getNode(left).type == HORIZONTAL_BELT || model.getNode(left).type == HORIZONTAL_ENGINE)
        {
            auto direction = model.getNode(left).direction;
            model.bufferCommand([position, direction, &model](){model->changeDirection(position, direction);}, [position, oldDirection, &model](){model->changeDirection(position, oldDirection);});
            return;
        }
    }

    if (model.inModel(right))
    {
        if (model.getNode(right).type == HORIZONTAL_BELT || model.getNode(right).type == HORIZONTAL_ENGINE)
        {
            auto direction = model.getNode(right).direction;
            model.bufferCommand([position, direction, &model](){model->changeDirection(position, direction);}, [position, oldDirection, &model](){model->changeDirection(position, oldDirection);});
            return;
        }
    }
};
