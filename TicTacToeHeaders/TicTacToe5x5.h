#pragma once
#ifndef TICTACTOE5X5_H
#define TICTACTOE5X5_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
template <typename T>
class TicTacToe5x5Board : public Board<T> {
public:
    TicTacToe5x5Board() {
        this->rows = 5;
        this->columns = 5;
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

    ~TicTacToe5x5Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    void set_player_names(const string& x_name, const string& o_name) {
        x_player_name = x_name;
        o_player_name = o_name;
    }

    string get_actual_winner_name() const {
        if (count_three_in_a_row('X') > count_three_in_a_row('O')) {
            return x_player_name;
        }
        if (count_three_in_a_row('O') > count_three_in_a_row('X')) {
            return o_player_name;
        }
        return "";
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

        cout << "\nScoreboard:\n";
        cout << "  " << x_player_name << " (X): " << count_three_in_a_row('X') << " three-in-a-row\n";
        cout << "  " << o_player_name << " (O): " << count_three_in_a_row('O') << " three-in-a-row\n";
    }



    bool is_empty(int x, int y) const {
        return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0;
    }

    int count_three_in_a_row(T current_player_symbol) const {
        int count = 0;

        // Check rows
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns - 2; ++j) {
                if (this->board[i][j] == current_player_symbol &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2]) {
                    count++;
                }
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; ++j) {
            for (int i = 0; i < this->rows - 2; ++i) {
                if (this->board[i][j] == current_player_symbol &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j]) {
                    count++;
                }
            }
        }

        // Check diagonals (top-left to bottom-right)
        for (int i = 0; i < this->rows - 2; ++i) {
            for (int j = 0; j < this->columns - 2; ++j) {
                if (this->board[i][j] == current_player_symbol &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2]) {
                    count++;
                }
            }
        }

        // Check diagonals (top-right to bottom-left)
        for (int i = 0; i < this->rows - 2; ++i) {
            for (int j = 2; j < this->columns; ++j) {
                if (this->board[i][j] == current_player_symbol &&
                    this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i][j] == this->board[i + 2][j - 2]) {
                    count++;
                }
            }
        }

        return count;
    }

    bool is_win() override {
        if (this->n_moves == 24) {
            return count_three_in_a_row('X') != count_three_in_a_row('O');
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == 24 && count_three_in_a_row('X') == count_three_in_a_row('O');
    }

    bool game_is_over() override {
        return this->n_moves == 24;
    }

private:
    string x_player_name;
    string o_player_name;
};

template <typename T>
class TicTacToe5x5Player : public Player<T> {
public:
    TicTacToe5x5Player(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int& x, int& y) override {
        cout << "\nEnter your move x [0-4] and y [0-4]: ";
        cin >> x >> y;
    }
};

template <typename T>
class TicTacToe5x5RandomPlayer : public RandomPlayer<T> {
public:
    TicTacToe5x5RandomPlayer(T symbol, const string& player_name)
            : RandomPlayer<T>(symbol), name(player_name) {
        srand(static_cast<unsigned int>(time(0)));
    }
    TicTacToe5x5RandomPlayer(T symbol)
            : RandomPlayer<T>(symbol) {
        srand(static_cast<unsigned int>(time(0)));
    }
    void getmove(int& x, int& y) override {
        x = rand() % 5;
        y = rand() % 5;

    }

    string getname() const { return name; }

private:
    string name;
};

#endif
