#include "CommandHistory.hpp"
#include <iostream>

CommandHistory::CommandHistory() : activeIndex(-1) {}

void CommandHistory::injectCommand(const Command& command)
{
    command.execute();
    activeCycle.addCommand(command);
}

void CommandHistory::bufferCommand(const Command& command)
{
    commandBuffer.push_back(command);
}

void CommandHistory::triggerBuffer()
{
    for (auto& command : commandBuffer)
    {
        injectCommand(command);
    }
    commandBuffer.clear();
}

void CommandHistory::saveCycle() {
    if (gameCycles.size() > activeIndex + 1) { 
        gameCycles.erase(gameCycles.begin() + activeIndex + 1, gameCycles.end());
    }
    gameCycles.push_back(activeCycle);
    activeCycle = Cycle();
    activeIndex++;
}

void CommandHistory::resetCycle()
{
    activeCycle.rewind();
    activeCycle = Cycle();
}

void CommandHistory::backward() 
{
    if (isActionInProgress) {
        return; // Ignore click if an action is already in progress
    }
    isActionInProgress = true;
    if (activeIndex >= 0) {

        gameCycles[activeIndex].rewind();
        activeIndex--;
    }
    isActionInProgress = false; // Reset the flag after action is completed
}

void CommandHistory::forward() {
    if (isActionInProgress) {
        return; // Ignore click if an action is already in progress
    }
    isActionInProgress = true;
    if (activeIndex + 1 < gameCycles.size()) {
        activeIndex++;
        gameCycles[activeIndex].execute();
    }
    isActionInProgress = false; // Reset the flag after action is completed
}