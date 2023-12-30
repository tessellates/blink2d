#include "TransformStrategy.hpp"

bool MoveStrategy::update(Transform& transform)
{
    return moveTowards(transform.position, moveTarget.position, moveSpeed);
}

MoveStrategy::MoveStrategy(const Transform& transform, float moveSpeed) : moveTarget(transform), moveSpeed(moveSpeed) {}
MoveStrategy::MoveStrategy(const ImVec2& pos, float moveSpeed) : moveTarget({pos}), moveSpeed(moveSpeed) {}
void MoveStrategy::setMoveTarget(const Transform& transform) {moveTarget = transform;}

/*
void EntryMoveStrategy::update(Transform& transform)
{
    moveVec(moveTarget.position, transform.position, moveSpeed, currentShift);
    transform = moveTarget + currentShift;
}

EntryMoveStrategy::EntryMoveStrategy(const Transform& transform, float moveSpeed) : moveTarget(transform), moveSpeed(moveSpeed) {}
void EntryMoveStrategy::setMoveTarget(const Transform& transform) {moveTarget = transform;}

void LeaveMoveStrategy::update(Transform& transform)
{
    moveVec(transform.position, moveTarget.position, moveSpeed, currentShift);
    transform += currentShift;
}

LeaveMoveStrategy::LeaveMoveStrategy(const Transform& transform, float moveSpeed) : moveTarget(transform), moveSpeed(moveSpeed) {}
void LeaveMoveStrategy::setMoveTarget(const Transform& transform) {moveTarget = transform;}*/