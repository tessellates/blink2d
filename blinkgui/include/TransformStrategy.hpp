#pragma once

#include "Transform.hpp"

class ITransformStrategy
{
public:
    virtual ~ITransformStrategy() = default;
    virtual bool update(Transform& transform) = 0;
};

class MoveStrategy : public ITransformStrategy
{
public:
    MoveStrategy() = default;
    MoveStrategy(const Transform& transform, float moveSpeed);
    MoveStrategy(const ImVec2& pos, float moveSpeed);
    bool update(Transform& transform) override;
    void setMoveTarget(const Transform& transform);

private:
    float moveSpeed; // if your move speed is texture width for example it move to side one texture's worth every game cycle. 
    Transform moveTarget;
};

/*
class EntryMoveStrategy : public ITransformStrategy
{
    EntryMoveStrategy() = default;
    EntryMoveStrategy(const Transform& transform, float moveSpeed);
    void update(Transform& transform) override;
    void setMoveTarget(const Transform& transform);

private:
    float moveSpeed; // if your move speed is texture width for example it move to side one texture's worth every game cycle. 
    Transform fromTarget;
    ImVec2 currentShift = ImVec2{0, 0};
};

class LeaveMoveStrategy : public ITransformStrategy
{
    LeaveMoveStrategy() = default;
    LeaveMoveStrategy(const Transform& transform, float moveSpeed);
    void update(Transform& transform) override;
    void setMoveTarget(const Transform& transform);

private:
    float moveSpeed; // if your move speed is texture width for example it move to side one texture's worth every game cycle. 
    Transform toTarget;
    ImVec2 currentShift = ImVec2{0, 0};
};*/
