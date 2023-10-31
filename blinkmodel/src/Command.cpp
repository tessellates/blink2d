#include "Command.hpp"

Command::Command(const std::function<void()>& forward, const std::function<void()>& back) : forward(forward), back(back) {}

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