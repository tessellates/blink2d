#include "ConnectModel.hpp"
#include "Command.hpp"
#include <algorithm> // For std::find
#include <random>

void printBoard(const std::vector<std::stack<int>>& board)
{
    std::cout << "\n" << std::endl;
    auto x = std::vector<std::string>(6, "-------");
    int dex = 0;
    for (auto q : board)
    {
        int qs = q.size();
        for (int i = 0; i < qs; ++i) {
            int p = q.top();
            q.pop();
            char strr = '-';
            if (p == 0)
            {
                strr = 'R';
            }
            else
            {
                strr = 'G';
            }
            x[6-qs+i][dex] = strr;
        }
        dex++;
    }
    for (auto& l : x)
    {
        std::cout << l << std::endl;
    }
}

// Constructors
ConnectModel::ConnectModel()
{
    intProperties.push_back(0);
    intProperties.push_back(0);
    board = std::vector<std::stack<int>>(7);
}

void ConnectModel::fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) {
    if (ent.type < 2)
    {
        board[cor.x].pop();
        //printBoard(board);
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
    printBoard(board);
}

bool matchValue(int player, const std::vector<std::stack<int>>& board, int row, int col) {
    if (col < 0 || col >= board.size()) {
        return false; // Invalid column
    }
    const std::stack<int>& q = board[col];
    if (row < 0 || row >= q.size()) {
        return false; // Invalid row
    }

    // Copy the stack to access the desired element
    std::stack<int> temp = q;
    for (int i = 1; i < q.size()-row; ++i) {
        temp.pop();
    }
    return player == temp.top();
}

std::optional<std::vector<Coordinate>> ConnectModel::checkWin(const std::vector<std::stack<int>>& board, int player) {
    int rows = 6;
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