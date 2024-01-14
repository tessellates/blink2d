
#include "GridEntityBuilder.hpp"


GridEntityBuilder::GridEntityBuilder(int nx, int ny, const ImVec2& gridSize, const ImVec2& gridLocation) : nx(nx), ny(ny), gridSize(gridSize), gridLocation(gridLocation)
{
    entity = std::make_unique<VisualEntity>();
    instruction = std::make_unique<RenderInstruction>();
    entitySize = ImVec2{gridSize.x/nx, gridSize.y/ny};
}

GridEntityBuilder& GridEntityBuilder::atLocation(const Coordinate& Coordinate) 
{
    entity->transform.position = absolutePosition(Coordinate);
    return *this;
}

GridEntityBuilder& GridEntityBuilder::instructionLayer(int layer) 
{
    instruction->layer = layer;
    return *this;
}

GridEntityBuilder& GridEntityBuilder::instructionLocation(const Coordinate& Coordinate) 
{
    instruction->relativeTransform.position = relativePosition(Coordinate);
    return *this;
}

GridEntityBuilder& GridEntityBuilder::instructionTexture(const BlinkTexture& texture) 
{
    instruction->setTextureStrategy(std::make_unique<StaticTextureStrategy>(texture));
    return *this;
}

GridEntityBuilder& GridEntityBuilder::instructionMoveStrategy(float gameTicks, const Coordinate& Coordinate) 
{
    instruction->ms = MoveStrategy(relativePosition(Coordinate), entitySize.x/gameTicks);
    return *this;
}

VisualEntity GridEntityBuilder::build() {
    auto v = std::move(*entity);
    entity = std::make_unique<VisualEntity>();
    return std::move(v);
}

GridEntityBuilder& GridEntityBuilder::addInstruction() 
{
    entity->renderInstructions.emplace_back(std::move(*instruction));
    instruction = std::make_unique<RenderInstruction>();
    return *this;
}

ImVec2 GridEntityBuilder::absolutePosition(const Coordinate& pos) const
{

    return ImVec2(gridLocation.x + pos.x * entitySize.x, gridLocation.y + pos.y * entitySize.y);
}

ImVec2 GridEntityBuilder::absolutePosition(const ImVec2& pos) const
{

    return ImVec2(gridLocation.x + pos.x * entitySize.x, gridLocation.y + pos.y * entitySize.y);
}


ImVec2 GridEntityBuilder::relativePosition(const Coordinate& pos) const
{
    return ImVec2(pos.x * entitySize.x, pos.y * entitySize.y);
}

Coordinate GridEntityBuilder::gridPosition(const ImVec2& pos) const
{
    ImVec2 relative = pos - gridLocation;
    int x = (relative.x) / entitySize.x;
    int y = (relative.y) / entitySize.y;
    return Coordinate(x, y);
}

// PRE SETS
VisualEntity entryAnimatedEntity(GridEntityBuilder& builder, const Coordinate& pos, const Coordinate& relativeEntry, const BlinkTexture& texture, float gameTicks, int layer)
{
    return std::move(builder.instructionLayer(layer).instructionTexture(texture).instructionMoveStrategy(gameTicks).instructionLocation(relativeEntry).atLocation(pos).addInstruction().build());
}

VisualEntity quadEntryAnimatedEntity(GridEntityBuilder& builder, const Coordinate& pos, int relativeEntry, const BlinkTexture& texture, float gameTicks, int layer)
{
    builder.instructionLayer(layer).instructionTexture(texture).instructionMoveStrategy(gameTicks).instructionLocation(Coordinate{relativeEntry, 0}).addInstruction();
    builder.instructionLayer(layer).instructionTexture(texture).instructionMoveStrategy(gameTicks).instructionLocation(Coordinate{0, relativeEntry}).addInstruction();
    builder.instructionLayer(layer).instructionTexture(texture).instructionMoveStrategy(gameTicks).instructionLocation(Coordinate{-relativeEntry, 0}).addInstruction();
    builder.instructionLayer(layer).instructionTexture(texture).instructionMoveStrategy(gameTicks).instructionLocation(Coordinate{0, -relativeEntry}).addInstruction();
    
    return std::move(builder.atLocation(pos).build());
}

VisualEntity staticEntity(GridEntityBuilder& builder, const Coordinate& pos, const BlinkTexture& texture, int layer)
{
    return std::move(builder.instructionLayer(layer).instructionTexture(texture).addInstruction().atLocation(pos).build());
}