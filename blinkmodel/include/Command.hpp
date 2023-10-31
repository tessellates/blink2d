#pragma once

#include <vector>
#include <functional>

class Command 
{
public:
    std::function<void()> forward;
    std::function<void()> back;
    
    Command(const std::function<void()>& forward, const std::function<void()>& back);
    void execute() const;
    void rewind() const;
};

class Cycle
{
public:
    std::vector<Command> commands = std::vector<Command>();

    Cycle() = default;
    void addCommand(const Command& command);
    void execute() const;
    void rewind() const;
};