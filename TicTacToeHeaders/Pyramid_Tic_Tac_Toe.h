#ifndef _PYRAMID_TIC_TAC_TOE_H
#define _PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

template <typename T>
class PyramidTicTacToe_Board: public Board<T> {
public:
    PyramidTicTacToe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    bool check_horizontal(int row, T symbol);
    bool check_vertical(int col, T symbol);
    bool check_diagonal(T symbol);
};

template <typename T>
class PyramidTicTacToe_Player : public Player<T> {
public:
    PyramidTicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class PyramidTicTacToe_RandomPlayer : public RandomPlayer<T> {
public:
    PyramidTicTacToe_RandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
PyramidTicTacToe_Board<T>::PyramidTicTacToe_Board() {
    this->rows = 3;
    this->columns = 5;
    this->n_moves = 0;

    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[2 * i + 1];
        for (int j = 0; j < 2 * i + 1; ++j) {
            this->board[i][j] = ' ';
        }
    }
}

template <typename T>
bool PyramidTicTacToe_Board<T>::update_board(int row, int col, T symbol) {
    if (row < 0 || row >= this->rows || col < 0 || col >= 2 * row + 1 || this->board[row][col] != ' ') {
        return false;
    }
    this->board[row][col] = symbol;
    this->n_moves++;
    return true;
}

template <typename T>
void PyramidTicTacToe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        cout << string((this->rows - i - 1) * 6, ' ');
        for (int j = 0; j < 2 * i + 1; ++j) {
            cout << "  |" << this->board[i][j] << "| ";
        }
        cout << endl;
    }
}

template <typename T>
bool PyramidTicTacToe_Board<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if (check_horizontal(i, 'X') || check_horizontal(i, 'O')) return true;
    }

    for (int col = 0; col < this->columns; ++col) {
        if (check_vertical(col, 'X') || check_vertical(col, 'O')) return true;
    }

    return check_diagonal('X') || check_diagonal('O');
}

template <typename T>
bool PyramidTicTacToe_Board<T>::check_horizontal(int row, T symbol) {
    for (int j = 0; j < 2 * row + 1 - 2; ++j) {
        if (this->board[row][j] == symbol &&
            this->board[row][j + 1] == symbol &&
            this->board[row][j + 2] == symbol) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool PyramidTicTacToe_Board<T>::check_vertical(int col, T symbol) {
    for (int i = 0; i <= this->rows - 3; ++i) {
        if (this->board[i][col] == symbol && this->board[i + 1][col] == symbol && this->board[i + 2][col] == symbol) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool PyramidTicTacToe_Board<T>::check_diagonal(T symbol) {
    return (this->board[0][0] == symbol && this->board[1][2] == symbol && this->board[2][4] == symbol) ||
           (this->board[0][0] == symbol && this->board[1][0] == symbol && this->board[2][0] == symbol);
}

template <typename T>
bool PyramidTicTacToe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramidTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
PyramidTicTacToe_Player<T>::PyramidTicTacToe_Player(string name, T symbol)
        : Player<T>(name, symbol) {
}

template <typename T>
void PyramidTicTacToe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
PyramidTicTacToe_RandomPlayer<T>::PyramidTicTacToe_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void PyramidTicTacToe_RandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % (2 * x + 1);
}

#endif //_PYRAMID_TIC_TAC_TOE_H
