#pragma once
#ifndef MISERETICTACTOEBOARD_H
#define MISERETICTACTOEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

template <typename T>
class MisereTicTacToeBoard : public Board<T> {
public:
    MisereTicTacToeBoard() {
        this->rows = 3;
        this->columns = 3;
        this->board = new T * [this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns];
        }
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    ~MisereTicTacToeBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (is_empty(x, y)) {
            this->board[x][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {

        cout << "\n     ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << j << " ";
        }
        cout << "\n   " << string(this->columns * 4 + 1, '-') << endl;

        for (int i = 0; i < this->rows; i++) {
            cout << setw(2) << i << " ";
            for (int j = 0; j < this->columns; j++) {
                char cell = this->board[i][j] ? this->board[i][j] : ' ';
                cout << "| " << cell << " ";
            }
            cout << "|\n   " << string(this->columns * 4 + 1, '-') << endl;
        }
        cout << endl;
    }


    bool is_empty(int x, int y) const {
        return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0;
    }

    bool has_three_in_a_row(T current_player_symbol) const {
        for (int i = 0; i < this->rows; ++i) {
            if (this->board[i][0] == current_player_symbol &&
                this->board[i][0] == this->board[i][1] &&
                this->board[i][0] == this->board[i][2]) {
                return true;
            }
        }

        for (int j = 0; j < this->columns; ++j) {
            if (this->board[0][j] == current_player_symbol &&
                this->board[0][j] == this->board[1][j] &&
                this->board[0][j] == this->board[2][j]) {
                return true;
            }
        }

        if (this->board[0][0] == current_player_symbol &&
            this->board[0][0] == this->board[1][1] &&
            this->board[0][0] == this->board[2][2]) {
            return true;
        }

        if (this->board[0][2] == current_player_symbol &&
            this->board[0][2] == this->board[1][1] &&
            this->board[0][2] == this->board[2][0]) {
            return true;
        }

        return false;
    }

    bool is_win() override {
        return false;
    }

    bool is_draw() override {
        return game_is_over();
    }

    bool game_is_over() override {
        return has_three_in_a_row('X') || has_three_in_a_row('O') || this->n_moves == 9;
    }

    bool player_loses(T symbol) const {
        return has_three_in_a_row(symbol);
    }


};
template <typename T>
class MisereTicTacToePlayer : public Player<T> {
public:
    MisereTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int& x, int& y);
};

template <typename T>
void MisereTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move x [0-2] and y [0-2]: ";
    cin >> x >> y;
}

template <typename T>
class MisereTicTacToeRandomPlayer : public MisereTicTacToePlayer<T> {
public:
    MisereTicTacToeRandomPlayer(T symbol, string name)
            : MisereTicTacToePlayer<T>(name, symbol){
        srand(time(0));
    }

    MisereTicTacToeRandomPlayer(T symbol)
            : RandomPlayer<T>(symbol) {
        srand(time(0));
    }


    void getmove(int& x, int& y) override {

        x = rand() % 3;
        y = rand() % 3;

    }
};

#endif
