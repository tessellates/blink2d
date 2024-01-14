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
    player = 0;
    gameOver = false;
    board = std::vector<std::stack<int>>(7);
    previewBoard = std::vector<std::stack<int>>(7);
    currentPreview = -1;
}

void ConnectModel::fireWin() 
{
    if (gameOver)
    {
        return;
    }
    win = checkWin(board, !player);
    if (win)
    {
        for (auto& pos : *win)
        {
            injectCommand(Command([&, pos](){this->change(pos, 2);}, [this, pos](){this->change(pos, !player);}));
        }
        injectCommand(Command([&](){this->gameOver = true;}, [this](){this->gameOver = false;}));
    }
}

void ConnectModel::play(int column)
{
    if (checkWin(board, !player))
    {
        return;
    }
    assert(column < 7);
    if (board[column].size() >= 6)
    {
        return;
    }
    removePreview();
    injectCommand(Command([column, this](){this->add(column);}, [column, this](){this->remove(column);}));


    fireWin();
    previewBoard = board;
    saveCycle();
}

void ConnectModel::removePreview()
{
    if (currentPreview == -1)
        return;
    for (auto& emit : removeConnectEntity)
    {
        emit({currentPreview, 7 - static_cast<int>(previewBoard[currentPreview].size())});
    }
    previewBoard[currentPreview].pop();
    currentPreview = -1;
}

void ConnectModel::addPreview()
{
    previewBoard[currentPreview].push(player);
    for (auto& emit : addConnectEntity)
    {
        emit({currentPreview, 7 - static_cast<int>(previewBoard[currentPreview].size())}, player+3);
    }
}

void ConnectModel::preview(int column)
{
    if (gameOver)
    {
        if (currentPreview > -1)
        {
            removePreview();
            return;
        }
        return;
    }

    if (currentPreview == column)
    {
        return;
    }

    if (currentPreview > -1)
    {
        if (currentPreview != column)
        {
            removePreview();
        }
    }

    if (currentPreview == -1)
    {
        if (column > -1 && static_cast<int>(previewBoard[column].size()) < 6)
        {
            currentPreview = column;
            addPreview();
        }
        return;
    }

}


void ConnectModel::add(int column)
{
    board[column].push(player);
    for (auto& emit : addConnectEntity)
    {
        emit({column, 7 - static_cast<int>(board[column].size())}, player);
    }
    player = !player;
}

void ConnectModel::remove(int column)
{
    for (auto& emit : removeConnectEntity)
    {
        emit({column, 7 - static_cast<int>(board[column].size())});
    }
    board[column].pop();
    player = !player;
}

void ConnectModel::change(const Coordinate& position, int color)
{
    for (auto& emit : changeConnectEntity)
    {
        emit(position, color);
    }
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