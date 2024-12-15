#ifndef FOUR_IN_ROW_BOARD_H
#define FOUR_IN_ROW_BOARD_H

#include"BoardGame_Classes.h"
#include <iomanip>

template <typename T>
class four_in_row_board :public  Board<T>
{
public:
    four_in_row_board() {
        this->rows = 6;
        this->columns = 7;
        this->board = new T * [this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new T[this->columns];
        }
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int row, int col, T symbol)  {

        for (int row = this->rows - 1; this->rows >= 0; row--)
        {
            if (this->board[row][col] == 0) {
                this->board[row][col] = symbol;
                this->n_moves++;
                return true;
            }
        }
        return false;
    }

    void display_board() {

        cout << "    "; 
        for (int j = 0; j < this->columns; j++) {
            cout << setw(5) << j; 
        }
        cout << endl;

        cout << "    "; 
        for (int j = 0; j < this->columns; j++) {
            cout << "-----";
        }
        cout << endl;

        for (int i = 0; i < this->rows; i++) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < this->columns; j++) {

                cout << setw(3) << (this->board[i][j] == '\0' ? ' ' : this->board[i][j]) << " |";
            }
            cout << endl;

            cout << "    ";
            for (int j = 0; j < this->columns; j++) {
                cout << "-----";
            }
            cout << "-" << endl;
        }
        cout << endl;
    }

    bool is_win()
    {
        for (int row = 0; row < this->rows; ++row) {
            for (int col = 0; col < this->columns - 3; ++col) {
                if (this->board[row][col] != 0 &&
                    this->board[row][col] == this->board[row][col + 1] &&
                    this->board[row][col] == this->board[row][col + 2] &&
                    this->board[row][col] == this->board[row][col + 3]) {
                    return true;
                }
            }
        }

        for (int row = 0; row < this->rows-3; row++) {
            for (int col = 0; col < this->columns ; col++) {
                if (this->board[row][col] != 0 &&
                    this->board[row][col] == this->board[row+1][col ] &&
                    this->board[row][col] == this->board[row+2][col ] &&
                    this->board[row][col] == this->board[row+3][col ]) {
                    return true;
                }
            }
        }


        for (int row = 3; row < this->rows; row++) {
            for (int col = 0; col < this->columns - 3; col++) {
                if (this->board[row][col] != 0 &&
                    this->board[row][col] == this->board[row - 1][col + 1] &&
                    this->board[row][col] == this->board[row - 2][col + 2] &&
                    this->board[row][col] == this->board[row - 3][col + 3]) {
                    return true;
                }
            }
        }

        for (int row = 3; row < this->rows; row++) {
            for (int col = 3; col <this->columns ; col++) {
                if (this->board[row][col] != 0 &&
                    this->board[row][col] == this->board[row - 1][col - 1] &&
                    this->board[row][col] == this->board[row - 2][col - 2] &&
                    this->board[row][col] == this->board[row - 3][col - 3]) {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_draw()
    {
        if (is_win())
            return false;
        for (int row = 0; row < this->rows; row++)
        {
            for (int col = 0; col < this->columns; col++)
            {
                if (this->board[row][col] == 0)
                    return false;
            }
        }
        return true;
    }
    bool game_is_over()
    {
        return (is_win() || is_draw());

    }
};

template <typename T>
class four_in_row_Player : public Player<T> {
public:
    four_in_row_Player(string n, T s) :Player<T>(n, s) {}

    void getmove(int& r, int& c)
    {
        cout << "It is " << this->name << "'s turn and your symbol is " << this->symbol ;
        cout << ", Please enter the column number [0->6]\n";
        cin >> c;
        while(c<0 || c>6)
        {
            cout << "Column is full. Try another column.\n";
            cin >> c;
        }

    }

};
template <typename T>
class four_in_row_Random_Player : public RandomPlayer<T> {
public:

    four_in_row_Random_Player(T symbol) :RandomPlayer<T>(symbol) {}

    void getmove(int& r, int& c)
    {
        c = rand() & 7;

    }
};
#endif