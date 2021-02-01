/*
** EPITECH PROJECT, 2021
** Sudoku_solver
** File description:
** Board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <iostream>

class Board {
    public:
        Board(char **av);
        ~Board() = default;

        bool solve(int x = 0, int y = 0);
        std::vector<std::vector<char>> getBoard() const { return _board; };

    private:
        char get(int x, int y) const { return _board[y][x]; };
        void inc(int x, int y) { _board[y][x]++; };
        void reset(int x, int y) { _board[y][x] = 0; };

        bool valid(int x, int y) const;

        void newLine() { _board.push_back(std::vector<char>()); };

        std::vector<std::vector<char>> _board;
};

std::ostream &operator<<(std::ostream &out, const Board &board);

#endif /* !BOARD_HPP_ */
