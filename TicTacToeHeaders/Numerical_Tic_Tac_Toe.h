#ifndef NUMERICAL_TIC_TAC_TOE
#define NUMERICAL_TIC_TAC_TOE

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

using namespace std;

char num;
set <char> s;

class numericalboard : public Board<char> {
protected:
    vector<vector<char>> board;
public:
    numericalboard() {
        board = vector<vector<char>>(3, vector<char>(3, '_'));
    }

    char get_cell(int x, int y) {
        if (x >= 0 && x < 3 && y >= 0 && y < 3) {
            return board[x][y];
        }
        return ' ';
    }

    void display_board() override {
        for (int i = 0; i < 3; ++i) {
            cout << "|";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << "|";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool update_board(int x, int y, char symbol) override {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == num) return false;
            }
        }
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == '_') {
            board[x][y] = num;
            return true;
        }
        return false;
    }

    bool CheckVertical(int x, int y) {
        int sum = 0, counter = 0;
        while (x < 3) {
            sum += (board[x][y] - '0');
            counter++;
            x++;
        }
        return (counter == 3 && sum == 15);
    }

    bool CheckHorizontal(int x, int y) {
        int sum = 0, counter = 0;
        while (y < 3) {
            sum += (board[x][y] - '0');
            counter++;
            y++;
        }
        return (counter == 3 && sum == 15);
    }

    bool CheckDiagonally() {
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < 3; ++i) {
            sum1 += (board[i][i] - '0');
            sum2 += (board[i][2 - i] - '0');
        }
        return (sum1 == 15 || sum2 == 15);
    }

    bool is_win() override {
        for (int i = 0; i < 3; i++) {
            if (CheckVertical(0, i) || CheckHorizontal(i, 0)) {
                return true;
            }
        }
        return CheckDiagonally();
    }

    bool is_draw() override {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == '_') return false;
            }
        }
        return !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class numericalPlayer : public Player<char> {
public:
    numericalPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        while (true) {
            cout << name << ", enter your move (row column number): ";
            cin >> x >> y >> num;

            if (x < 1 || x > 3 || y < 1 || y > 3) {
                cout << "Invalid Place.Please enter a place from 1 to 3\n";
                continue;
            }
            if (num < '1' || num > '9') {
                cout << "Invalid number. Please enter a number between 1 and 9.\n";
                continue;
            }
            if (symbol == 'o' && (num - '0') % 2 == 0) {
                cout << "Please enter an odd number.\n";
                continue;
            }
            if (symbol == 'e' && (num - '0') % 2 != 0) {
                cout << "Please enter an even number.\n";
                continue;
            }

            x--; y--;
            return;
        }
    }
};

class numericalRandomPlayer : public RandomPlayer<char> {
private:
    numericalboard& board;

public:
    numericalRandomPlayer(const string& name, numericalboard& board)
            : RandomPlayer(' '), board(board) {}

    void getmove(int& x, int& y) override {
        srand(static_cast<unsigned>(time(0)));

        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board.get_cell(x, y) != '_');

        if ((num - '0') % 2 == 0) {
            char arr[] = {'1', '3', '5', '7', '9'};
            int i;
            do {
                i = rand() % 5;
            } while(s.count(arr[i]));
            s.insert(num = arr[i]);
        } else {
            char arr[] = {'2', '4', '6', '8'};
            int i;
            do {
                i = rand() % 4;
            } while(s.count(arr[i]));
            s.insert(num = arr[i]);
        }

    }

};

#endif // NUMERICAL_TIC_TAC_TOE
