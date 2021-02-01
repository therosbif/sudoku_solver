/*
** rosbif
** Sudoku_solver
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include "Board.hpp"

#define USAGE "USAGE: " << std::endl \
                        << av[0] << " file_path"

Board::Board(char **av)
{
    std::ifstream file(av[1]);
    char c;
    int idx = 0;

    if (!file.is_open()) {
        std::cerr << USAGE << std::endl;
        exit(2);
    }
    newLine();
    while (file.read(&c, 1)) {
        if (c == '\n' && _board.at(idx).size() == 9) {
            idx++;
            newLine();
        }
        if (c <= '9' && c >= '0')
            _board.at(idx).push_back(c - '0');
    }
    _board.pop_back();
    if (_board.size() != 9) {
        std::cerr << "Invalid board" << std::endl;
        exit(3);
    }
    for (auto i : _board) {
        if (i.size() != 9) {
            std::cerr << "Invalid board" << std::endl;
            exit(3);
        }
    }
    file.close();
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
    auto _board = board.getBoard();

    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) out << std::endl;
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) out << " ";
            out << (char)(_board[i][j] + '0');
        }
        out << std::endl;
    }
    return out;
}

bool Board::valid(int x, int y) const
{
    char c = get(x, y);

    for (int i = 0; i < 9; i++) {
        if ((get(i, y) == c && x != i) || (get(x, i) == c && y != i))
            return false;
    }
    for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++) {
        for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++) {
            if (get(i, j) == c && (i != x || j != y))
                return false;
        }
    }
    return true;
}

bool Board::solve(int x, int y)
{
    if (y > 8) return true;
    if (get(x, y) == 0) {
        inc(x, y);
        for (; get(x, y) <= 9; inc(x, y)) {
            if (valid(x, y)) {
                if (solve((x == 8) ? 0 : x + 1, (x == 8) ? y + 1 : y))
                    return true;
            }
        }
        reset(x, y);
        return false;
    }
    return solve((x == 8) ? 0 : x + 1, (x == 8) ? y + 1 : y);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << USAGE << std::endl;
        return 1;
    }

    Board board(av);
    if (board.solve())
        std::cout << board;
    else std::cerr << "No Solution" << std::endl;
    return 0;
}
