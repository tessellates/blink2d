#pragma once

#include "Coordinate.hpp"
#include <stack>
#include "CommandHistory.hpp"
#include "Direction.hpp"
#include <optional>

class ConnectModel : public CommandHistory
{
public:
    ConnectModel();
    void play(int column);
    void preview(int column);
    void fireWin();
    std::optional<std::vector<Coordinate>> checkWin(const std::vector<std::stack<int>>& board, int player);

    void add(int column);
    void remove(int column);
    void change(const Coordinate&, int);


    void addPreview();
    void removePreview();
    
public:
    std::vector<std::function<void(const Coordinate&, int)>> addConnectEntity;    
    std::vector<std::function<void(const Coordinate&)>> removeConnectEntity;    
    std::vector<std::function<void(const Coordinate&, int)>> changeConnectEntity;    

    int player;
    bool gameOver;

    std::vector<std::stack<int>> board;
    std::optional<std::vector<Coordinate>> win;

    int currentPreview = -1;
    std::vector<std::stack<int>> previewBoard;

};
