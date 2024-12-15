#pragma once
#include "BoardGame_classes.h"
#include <iostream>
#include <iomanip>
template <typename T>
class ultimate_tic_tac_toe_board :public Board<T>
{
private:
	T board[9][9];
	T small_board[3][3];
public:
	ultimate_tic_tac_toe_board()
	{
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = 0;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				small_board[i][j] = 0;
			}
		}

	}
	bool update_board(int x, int y, T symbol)
	{
		if (x < 0 || x >= 9 || y < 0 || y >= 9 || board[x][y] != 0) {
			return false;
		}

		board[x][y] = symbol;
		return true;
	}

	void update_small_board(int small_x, int small_y, T symbol)
	{

		small_board[small_x][small_y] = symbol;

	}

	void display_board()
	{
		small_board_winner();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << "(" << i << "," << j << ")";
				cout << setw(2) << (board[i][j] ? board[i][j] : ' ') << " |";
			}
			cout << endl;
		}

		cout << "\nSmall Board Winners (X or O):\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << setw(3) << (small_board[i][j] ? small_board[i][j] : '-');
			}
			cout << endl;
		}

	}

	bool is_win()
	{
		for (int i = 0; i < 3; i++) {

			if (small_board[i][0] == small_board[i][1] &&
				small_board[i][0] == small_board[i][2] &&
				small_board[i][0] != 0) {
				return true;
			}
			if (small_board[0][i] == small_board[1][i] &&
				small_board[0][i] == small_board[2][i] &&
				small_board[0][i] != 0) {
				return true;
			}
		}

		if (small_board[0][0] == small_board[1][1] &&
			small_board[0][0] == small_board[2][2] &&
			small_board[0][0] != 0) {
			return true;
		}
		if (small_board[0][2] == small_board[1][1] &&
			small_board[0][2] == small_board[2][0] &&
			small_board[0][2] != 0) {
			return true;
		}

		return false;

	}
	void small_board_winner()
	{
		for (int rows = 0; rows < 9; rows++)
		{
			for (int col = 0; col < 7; col += 3)
			{
				if (board[rows][col] == board[rows][col + 1] && board[rows][col + 1] == board[rows][col + 2] && board[rows][col] != ' ' && board[rows][col] != 0 && small_board[int(rows / 3)][int(col / 3)] == 0)
				{
					update_small_board((rows / 3), (col / 3), board[rows][col]);
					return;
				}
			}
		}

		// Check columns
		for (int col = 0; col < 9; col++)
		{
			for (int rows = 0; rows < 7; rows += 3)
			{
				if (board[rows][col] == board[rows + 1][col] && board[rows + 1][col] == board[rows + 2][col] && board[rows][col] != ' ' && board[rows][col] != 0 && small_board[int(rows / 3)][int(col / 3)] == 0)
				{
					update_small_board(floor(rows / 3), (col / 3), board[rows][col]);
					return;
				}
			}
		}
		// Check diagonals
		for (int col = 0; col < 7; col += 3)
		{
			for (int rows = 0; rows < 7; rows += 3)
			{
				if (board[rows][col] == board[rows + 1][col + 1] && board[rows + 1][col + 1] == board[rows + 2][col + 2] && board[rows][col] != ' ' && board[rows][col] != 0 && small_board[int(rows / 3)][int(col / 3)] == 0)
				{
					update_small_board((rows / 3), (col / 3), board[rows][col]);
					return;
				}
			}
		}

		for (int col = 0; col < 7; col += 3)
		{
			for (int rows = 0; rows < 7; rows += 3)
			{
				if (board[rows][col + 2] == board[rows + 1][col + 1] && board[rows + 1][col + 1] == board[rows + 2][col] && board[rows][col + 2] != ' ' && board[rows][col + 2] != 0 && small_board[int(rows / 3)][int(col / 3)] == 0)
				{
					update_small_board((rows / 3), (col / 3), board[rows][col + 2]);
					return;
				}
			}
		}
	}
	bool is_draw()
	{
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == 0) {
					return false;
				}
			}
		}
		return !is_win();
	}
	bool game_is_over()
	{
		return is_win() || is_draw();

	}
};
template<typename T>
class ultimate_tic_tac_toe_player : public Player <T>
{
public:
	ultimate_tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol)
	{

	}
	void getmove(int& x, int& y)
	{
		cout << this->name << " Please enter the cell u want to play ";
		cin >> x >> y;

	}
};

template<typename T>
class ultimate_tic_tac_toe_random_player :public RandomPlayer<T>
{
public:
	ultimate_tic_tac_toe_random_player(T symbol) :RandomPlayer<T>(symbol)
	{

	}
	void getmove(int& x, int& y)
	{

		x = rand() % 9;
		y = rand() % 9;
	}
};