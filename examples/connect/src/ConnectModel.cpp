#include "ConnectModel.hpp"
#include "Command.hpp"
#include <algorithm> // For std::find
#include <random>

// Constructors
ConnectModel::ConnectModel()
{
    intProperties.push_back(0);
    intProperties.push_back(0);
    board = std::vector<std::queue<int>>(7);
}

void ConnectModel::fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) {
    if (ent.type < 2)
    {
        board[cor.x].pop();
    }
    GameState::fireRemoveEntity(cor, ent);
}

void ConnectModel::fireAddEntity(const Coordinate& cor, const GridEntity& ent) {
    if (ent.type < 2)
    {
        board[cor.x].push(ent.type);
    }
    GameState::fireAddEntity(cor, ent);
}

void ConnectModel::fireWin() 
{
    if (intProperties[ConnectProperties::END] > 0)
    {
        return;
    }
    win = checkWin(board, !intProperties[ConnectProperties::PLAYER]);
    if (win)
    {
        for (auto& pos : *win)
        {
            GridEntity ent = GridEntity(pos, !intProperties[ConnectProperties::PLAYER]+3);
            removeEntity(pos, ent);
            ent.type = 2;
            addEntity(pos, ent);
            changeProperty(ConnectProperties::END, 1);
        }
        saveCycle();
    }
}


void ConnectModel::play(int column)
{
    if (checkWin(board, !intProperties[ConnectProperties::PLAYER]))
    {
        return;
    }
    assert(column < 7);
    if (board[column].size() >= 6)
    {
        return;
    }
    Coordinate pos = Coordinate(column, 6 - board[column].size());
    GridEntity ent = GridEntity(pos, intProperties[ConnectProperties::PLAYER]);
    addEntity(pos, ent);
    changeProperty(ConnectProperties::PLAYER, !intProperties[ConnectProperties::PLAYER]);
    saveCycle();
}

bool matchValue(int player, const std::vector<std::queue<int>>& board, int row, int col) {
    if (col < 0 || col >= board.size()) {
        return false; // Invalid column
    }
    const std::queue<int>& q = board[col];
    if (row < 0 || row >= q.size()) {
        return false; // Invalid row
    }

    // Copy the queue to access the desired element
    std::queue<int> temp = q;
    for (int i = 0; i < row; ++i) {
        temp.pop();
    }
    return player == temp.front();
}

std::optional<std::vector<Coordinate>> ConnectModel::checkWin(const std::vector<std::queue<int>>& board, int player) {
    int rows = board.size();
    int cols = 7;
    std::vector<Coordinate> winningPositions;
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (matchValue(player, board, r, c)) {
                // Check horizontally
                if (matchValue(player, board, r, c + 1) && matchValue(player, board, r, c + 2) && matchValue(player, board, r, c + 3)) {
                    for (int i = 0; i < 4; ++i) winningPositions.push_back({c + i, 6 - r});
                    return winningPositions;
                }

                // getValueAt vertically
                if (matchValue(player, board, r + 1, c) && matchValue(player, board, r + 2, c) && matchValue(player, board, r + 3, c)) 
                {
                    for (int i = 0; i < 4; ++i) winningPositions.push_back({c, 6 - (r + i)});
                    return winningPositions;
                }

                // getValueAt diagonal (down-right)
                if (matchValue(player, board, r + 1, c + 1) && matchValue(player, board, r + 2, c + 2) && matchValue(player, board, r + 3, c + 3)) {
                    for (int i = 0; i < 4; ++i) winningPositions.push_back({c + i, 6 - (r + i)});
                    return winningPositions;
                }

                // getValueAt diagonal (up-right)
                if (matchValue(player, board, r - 1, c + 1) && matchValue(player, board, r - 2, c + 2) && matchValue(player, board, r - 3, c + 3)) {
                    for (int i = 0; i < 4; ++i) winningPositions.push_back({c + i, 6 - (r - i)});
                    return winningPositions;
                }
            }
        }
    }
    return {}; // No win found
}