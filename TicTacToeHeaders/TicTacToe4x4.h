#pragma once
#ifndef TICTACTOE4X4_H
#define TICTACTOE4X4_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

template <typename T>
class TicTacToe4x4Board : public Board<T> {
public:

    TicTacToe4x4Board() {
        this->rows = 4;
        this->columns = 4;
        this->board = new T * [this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns]();
        }

        this->board[0][0] = 'O';
        this->board[0][1] = 'X';
        this->board[0][2] = 'O';
        this->board[0][3] = 'X';

        this->board[3][0] = 'X';
        this->board[3][1] = 'O';
        this->board[3][2] = 'X';
        this->board[3][3] = 'O';
    }

    ~TicTacToe4x4Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    void display_board() override {
        cout << "\n   0   1   2   3\n";
        cout << "  -----------------\n";
        for (int i = 0; i < this->rows; i++) {
            cout << i << " ";
            for (int j = 0; j < this->columns; j++) {
                char cell = this->board[i][j] ? this->board[i][j] : ' ';
                cout << "| " << cell << " ";
            }
            cout << "|\n  -----------------\n";
        }
    }

    bool is_empty(int x, int y) const {
        return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0;
    }

    bool is_valid_move(int from_x, int from_y, int to_x, int to_y, T symbol) {

        if (this->board[from_x][from_y] != symbol) return false;

        return is_empty(to_x, to_y) &&
               ((abs(to_x - from_x) == 1 && to_y == from_y) || (abs(to_y - from_y) == 1 && to_x == from_x));
    }

    bool update_board(int x, int y, T symbol) override {

        int from_x = x / 10, from_y = x % 10;
        int to_x = y / 10, to_y = y % 10;

        if (is_valid_move(from_x, from_y, to_x, to_y, symbol)) {
            this->board[to_x][to_y] = symbol;
            this->board[from_x][from_y] = 0; 
            return true;
        }

        cout << "Invalid move! Try again.\n";
        return false;
    }

    bool is_win() override {
        return check_alignment('X') || check_alignment('O');
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    bool is_draw() override {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == 0) return false;
            }
        }
        return !is_win();
    }

    T** get_board() const {
        return this->board;
    }

private:
    bool check_alignment(T symbol) {
        // Check horizontal and vertical alignments
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] == symbol && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) {
                    return true;
                }
                if (this->board[j][i] == symbol && this->board[j + 1][i] == symbol && this->board[j + 2][i] == symbol) {
                    return true;
                }
            }
        }

        // Check diagonal alignments
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                    return true;
                }
                if (this->board[i][j + 2] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j] == symbol) {
                    return true;
                }
            }
        }
        return false;
    }


};

template <typename T>
class TicTacToe4x4Player : public Player<T> {
public:
    TicTacToe4x4Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        int from_x, from_y, to_x, to_y;

        auto* board = static_cast<TicTacToe4x4Board<T>*>(this->boardPtr);
        T** board_array = board->get_board();

        do {
            cout << this->getname() << " (" << this->getsymbol() << "), choose the token to move (row and column 0-3): ";
            cin >> from_x >> from_y;
        } while (board_array[from_x][from_y] != this->getsymbol());

        do {
            cout << "Choose the destination (row and column 0-3): ";
            cin >> to_x >> to_y;
        } while (!board->is_valid_move(from_x, from_y, to_x, to_y, this->getsymbol()));

        x = (from_x * 10) + from_y; 
        y = (to_x * 10) + to_y; 
    }
};


template <typename T>
class TicTacToe4x4RandomPlayer : public RandomPlayer<T> {
public:
    TicTacToe4x4RandomPlayer(T symbol, const string& player_name)
            : RandomPlayer<T>(symbol), name(player_name) {
        srand(static_cast<unsigned int>(time(0))); 
    }

    TicTacToe4x4RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        int from_x, from_y, to_x, to_y;

        auto* board = static_cast<TicTacToe4x4Board<T>*>(this->boardPtr); 
        T** board_array = board->get_board();

        do {
            from_x = rand() % 4;
            from_y = rand() % 4;
        } while (board_array[from_x][from_y] != this->getsymbol());

        do {
            to_x = rand() % 4;
            to_y = rand() % 4;
        } while (!board->is_valid_move(from_x, from_y, to_x, to_y, this->getsymbol()));

        x = (from_x * 10) + from_y; 
        y = (to_x * 10) + to_y;
    }


private:
    string name;
};


#endif
