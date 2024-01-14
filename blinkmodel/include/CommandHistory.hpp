#pragma once

#include "Command.hpp"
#include <vector>

class CommandHistory {
public:
    CommandHistory();

    void injectCommand(const Command& command);
    void bufferCommand(const Command& command);
    void triggerBuffer();
    void saveCycle();
    void resetCycle();
    void backward();
    void forward();

private:
    std::vector<Command> commandBuffer;
    std::vector<Cycle> gameCycles;
    Cycle activeCycle;
    int activeIndex;

    bool isActionInProgress = false;
};
