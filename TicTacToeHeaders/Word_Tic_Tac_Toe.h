#ifndef _WORD_TIC_TAC_TOE_H
#define _WORD_TIC_TAC_TOE_H

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

using namespace std;

template <typename T>
class WordTicTacToeBoard {
public:
    WordTicTacToeBoard(int rows, int columns);
    void displayBoard() const;
    bool makeMove(int row, int col, T letter);
    bool is_win(const set<string>& dictionary);
    bool checkHorizontal(int row, int col, const T& letter, const set<string>& dictionary);
    bool checkVertical(int row, int col, const T& letter, const set<string>& dictionary);
    bool checkDiagonal(int row, int col, const T& letter, const set<string>& dictionary);

    vector<vector<T>>& getBoard();

private:
    int rows, columns;
    vector<vector<T>> board;

    bool checkWord(const set<string>& dictionary, const string& word);
};

template <typename T>
vector<vector<T>>& WordTicTacToeBoard<T>::getBoard() {
    return board;
}

template <typename T>
class RandomWordTicTacToePlayer : public Player<T> {
public:
    RandomWordTicTacToePlayer(T symbol);
    void getmove(int& x, int& y);

    char getRandomLetter();

    WordTicTacToeBoard<T>* boardPtr;
};

template <typename T>
char RandomWordTicTacToePlayer<T>::getRandomLetter() {
    return 'A' + rand() % 26;
}

template <typename T>
WordTicTacToeBoard<T>::WordTicTacToeBoard(int rows, int columns) : rows(rows), columns(columns) {
    board.resize(rows, vector<T>(columns, 0));
}

template <typename T>
void WordTicTacToeBoard<T>::displayBoard() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << "| " << (board[i][j] == 0 ? ' ' : board[i][j]) << " ";
        }
        cout << "|\n";
        if (i < rows - 1) {
            cout << "-------------\n";
        }
    }
}

template <typename T>
bool WordTicTacToeBoard<T>::makeMove(int row, int col, T letter) {
    if (row >= 0 && row < rows && col >= 0 && col < columns && board[row][col] == 0) {
        board[row][col] = letter;
        return true;
    }
    return false;
}

template <typename T>
bool WordTicTacToeBoard<T>::checkWord(const set<string>& dictionary, const string& word) {
    string uppercaseWord = word;
    for (auto& ch : uppercaseWord) ch = toupper(ch);
    return dictionary.find(uppercaseWord) != dictionary.end();
}

template <typename T>
bool WordTicTacToeBoard<T>::checkHorizontal(int row, int col, const T& letter, const set<string>& dictionary) {
    string word = "";
    for (int i = 0; i < columns; ++i) {
        word += board[row][i];
    }
    return checkWord(dictionary, word);
}

template <typename T>
bool WordTicTacToeBoard<T>::checkVertical(int row, int col, const T& letter, const set<string>& dictionary) {
    string word = "";
    for (int i = 0; i < rows; ++i) {
        word += board[i][col];
    }
    return checkWord(dictionary, word);
}

template <typename T>
bool WordTicTacToeBoard<T>::checkDiagonal(int row, int col, const T& letter, const set<string>& dictionary) {
    string word1 = "", word2 = "";

    if (row == col) {
        for (int i = 0; i < rows; i++) {
            word1 += board[i][i];
        }
    }

    if (row + col == columns - 1) {
        for (int i = 0; i < rows; i++) {
            word2 += board[i][columns - 1 - i];
        }
    }

    return checkWord(dictionary, word1) || checkWord(dictionary, word2);
}

template <typename T>
bool WordTicTacToeBoard<T>::is_win(const set<string>& dictionary) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] != 0) {
                if (checkHorizontal(i, j, board[i][j], dictionary) ||
                    checkVertical(i, j, board[i][j], dictionary) ||
                    checkDiagonal(i, j, board[i][j], dictionary)) {
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename T>
RandomWordTicTacToePlayer<T>::RandomWordTicTacToePlayer(T symbol) : Player<T>("Computer", symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void RandomWordTicTacToePlayer<T>::getmove(int& x, int& y) {
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (this->boardPtr->getBoard()[x][y] != 0);
}

set<string> loadDictionary(const string& filename) {
    set<string> dictionary;
    ifstream file(filename);
    string word;
    while (file >> word) {
        for (auto& ch : word) ch = toupper(ch);
        dictionary.insert(word);
    }
    return dictionary;
}

#endif //_WORD_TIC_TAC_TOE_H
