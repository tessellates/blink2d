#include "Command.hpp"
#include "GameState.hpp"

Command* Command::Command(std::function<void> forward, std::function<void> back) foward(foward), back(back) {}

void Command::execute() const
{
    forward();
}

void Command::rewind() const
{
    back();
}

// For CompositeStateCommand class
void Cycle::execute() const {
    // Iterating forward and executing each command in the composite
    for(auto it = commands.begin(); it != commands.end(); ++it) {
        (*it).execute();
    }
    return true; // Assuming the method should return true on successful execution
}

void Cycle::rewind() const {
    // Iterating backward and rewinding each command in the composite
    for(auto it = commands.rbegin(); it != commands.rend(); ++it) {
        (*it).rewind();
    }
}

void Cycle::addCommand(const Command& command)
{
    commands.push_back(command);
}