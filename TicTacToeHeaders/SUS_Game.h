#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class SUSBoard : public Board<char> {
public:
    SUSBoard() {
        rows = 3;
        columns = 3;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                board[i][j] = ' ';
            }
        }
    }

    ~SUSBoard() {}

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {    // mtnsash el arkam b3den
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << (j > 0 ? " | " : "") << (board[i][j] == ' ' ? " " : string(1, board[i][j]));
            }
            cout << endl;
            if (i < rows - 1) cout << "---------\n";
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (Check_Sequence(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_draw();
    }

    char board[3][3];

    char (&get_board())[3][3] {
        return board;
    }

private:

    bool Check_Sequence(int x, int y) {  // mtnsash kol el e7tmalat
        if (board[x][y] != 'S') return false;

        if (y + 2 < columns && board[x][y + 1] == 'U' && board[x][y + 2] == 'S') return true;
        if (x + 2 < rows && board[x + 1][y] == 'U' && board[x + 2][y] == 'S') return true;
        if (x + 2 < rows && y + 2 < columns && board[x + 1][y + 1] == 'U' && board[x + 2][y + 2] == 'S') return true;
        if (x + 2 < rows && y - 2 >= 0 && board[x + 1][y - 1] == 'U' && board[x + 2][y - 2] == 'S') return true;

        return false;
    }
};

bool is_sus_sequence(char (&board)[3][3], int row, int col) {
    if (col <= 1 && board[row][col] == 'S' && board[row][col+1] == 'U' && board[row][col+2] == 'S')
        return true;
    if (col >= 1 && col <= 2 && board[row][col-1] == 'S' && board[row][col] == 'U' && board[row][col+1] == 'S')
        return true;
    if (col >= 2 && board[row][col-2] == 'S' && board[row][col-1] == 'U' && board[row][col] == 'S')
        return true;

    if (row <= 1 && board[row][col] == 'S' && board[row+1][col] == 'U' && board[row+2][col] == 'S')
        return true;
    if (row >= 1 && row <= 2 && board[row-1][col] == 'S' && board[row][col] == 'U' && board[row+1][col] == 'S')
        return true;
    if (row >= 2 && board[row-2][col] == 'S' && board[row-1][col] == 'U' && board[row][col] == 'S')
        return true;

    if (row == col && row <= 1 && board[row][col] == 'S' && board[row+1][col+1] == 'U' && board[row+2][col+2] == 'S')
        return true;
    if (row == col && row >= 1 && row <= 2 && board[row-1][col-1] == 'S' && board[row][col] == 'U' && board[row+1][col+1] == 'S')
        return true;
    if (row == col && row >= 2 && board[row-2][col-2] == 'S' && board[row-1][col-1] == 'U' && board[row][col] == 'S')
        return true;

    if (row + col == 2 && row <= 1 && board[row][col] == 'S' && board[row+1][col-1] == 'U' && board[row+2][col-2] == 'S')
        return true;
    if (row + col == 2 && row >= 1 && row <= 2 && board[row-1][col+1] == 'S' && board[row][col] == 'U' && board[row+1][col-1] == 'S')
        return true;
    if (row + col == 2 && row >= 2 && board[row-2][col+2] == 'S' && board[row-1][col+1] == 'U' && board[row][col] == 'S')
        return true;

    return false;
}

class SUSPlayer : public Player<char> {
public:
    SUSPlayer(string n) : Player<char>(n, ' ') {}

    void getmove(int& x, int& y) override {
        do {
            int square;
            cout << "\n" << this->name << " enter your move (square number 1-9): ";
            while (!(cin >> square) || square < 1 || square > 9) {
                cout << "Invalid input. Please enter a number between 1 and 9: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            x = (square - 1) / 3;
            y = (square - 1) % 3;

            SUSBoard* susBoard = dynamic_cast<SUSBoard*>(boardPtr);
            if (!susBoard) {
                cerr << "Invalid.\n";
                exit(EXIT_FAILURE);
            }

            if (susBoard->board[x][y] != ' ') {
                cout << "This position is already filled.Please choose another position\n";
            } else {
                break;
            }
        } while (true);

        cout << this->getname() << ", choose your symbol ('S' or 'U'): ";
        while (!(cin >> symbol) || (symbol != 'S' && symbol != 'U' && symbol != 's' && symbol != 'u')) {
            cout << "Invalid input. Please choose 'S' or 'U': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        symbol = toupper(symbol);
    }
};

class SUSRandomPlayer : public Player<char> {
public:
    SUSRandomPlayer(string n, Board<char>* b) : Player<char>(n, ' ') {
        this->boardPtr = b;
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        SUSBoard* susBoard = dynamic_cast<SUSBoard*>(boardPtr);
        if (!susBoard) {
            cerr << "Invalid.\n";
            exit(EXIT_FAILURE);
        }

        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (susBoard->get_board()[x][y] != ' ');

        symbol = (rand() % 2 == 0) ? 'S' : 'U';
        cout << "\n" << this->getname() << " chose square " << (x * 3 + y + 1) << " with symbol " << symbol << "\n";
    }
};

#endif
