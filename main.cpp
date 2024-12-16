#include <iostream>
#include "BoardGame_Classes.h"
#include "Pyramid_Tic_Tac_Toe.h"
#include "four_in_row_board.h"
#include "TicTacToe5x5.h"
#include "Word_Tic_Tac_Toe.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "MisereTicTacToe.h"
#include "TicTacToe4x4.h"
#include "ultimate_tic_tac_toe_board.h"
#include "SUS_Game.h"

using namespace std;

void runSUSGame() {
    while (true) {
        int score1 = 0, score2 = 0;
        int currentPlayer = 0;

        cout << "1. Two players\n";
        cout << "2. Player vs Random moves\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1, 2, or 3): ";

        int choice;
        while (!(cin >> choice) || (choice != 1 && choice != 2 && choice != 3)) {
            cout << "Invalid input. Please enter a valid choice (1, 2, or 3): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 3) {
            cout << "\nGoodbye.\n_\n";
            break;
        }

        string player1_name, player2_name;

        cout << "Enter the name for Player 1: ";
        cin.ignore();
        getline(cin, player1_name);

        SUSBoard board;
        SUSPlayer player1(player1_name);

        Player<char>* player2;

        if (choice == 1) {
            cout << "Enter the name for Player 2: ";
            getline(cin, player2_name);
            player2 = new SUSPlayer(player2_name);
        }
        else {
            player2_name = "Random Player";
            player2 = new SUSRandomPlayer(player2_name, &board);
        }

        player1.setBoard(&board);
        player2->setBoard(&board);

        Player<char>* players[2] = { &player1, player2 };

        GameManager<char> game(&board, players);

        while (!board.game_is_over()) {
            int x, y;
            board.display_board();
            players[currentPlayer]->getmove(x, y);

            while (!board.update_board(x, y, players[currentPlayer]->getsymbol())) {
                cout << "Invalid move. Try again.\n";
                players[currentPlayer]->getmove(x, y);
            }

            if (is_sus_sequence(board.get_board(), x, y)) {
                cout << "\n__" << players[currentPlayer]->getname() << " scores a point!\n";
                if (currentPlayer == 0) {
                    score1++;
                }
                else {
                    score2++;
                }
            }

            currentPlayer = 1 - currentPlayer;
        }

        cout << "\n_\n\nFinal Scores: " << player1_name << ": " << score1 << " | " << player2_name << ": " << score2 << "\n\n";

        if (score1 > score2) {
            cout << player1_name << " wins!\n";
        }
        else if (score2 > score1) {
            cout << player2_name << " wins!\n";
        }
        else {
            cout << "Draw!\n";
        }

        delete player2;

        cout << "\n_\n\nGame Over!\n";
        cout << "1. Play Again\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";

        int play_again_choice;
        while (!(cin >> play_again_choice) || (play_again_choice != 1 && play_again_choice != 2)) {
            cout << "Invalid input.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (play_again_choice == 2) {
            cout << "\nThanks for playing SUS game.\n_\n";
            break;
        }
    }
}


void runUltimateTicTacToe(){
    int x, y;
    bool first_player_turn = true;
    cout << "Welcome to Ultimate Tic Tac Toe game\n";
    int choice;
    int rows = 9;
    int columns = 9;
    Player<char>* players[2];
    ultimate_tic_tac_toe_board<char>* B = new ultimate_tic_tac_toe_board<char>();
    string first_player_name, second_player_name;

    cout << "Choose first player type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";

    while (true) {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 for Human or 2 for Random Computer: ";
        }
        else {
            break;
        }
    }
    
    cin.ignore();
    
    if (choice == 1) {
        cout << "Enter first player name: ";
        while (true) {
            getline(cin, first_player_name);
            if (first_player_name.empty()) {
                cout << "Name cannot be empty. Please enter a valid name: ";
            }
            else {
                break;
            }
        }
        players[0] = new ultimate_tic_tac_toe_player<char>(first_player_name, 'X');
    }
    else {
        players[0] = new ultimate_tic_tac_toe_random_player<char>('X');
    }

    cout << "Choose second player type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";

    while (true) {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 for Human or 2 for Random Computer: ";
        }
        else {
            break;
        }
    }

    cin.ignore();

    if (choice == 1) {
        cout << "Enter second player name: ";
        while (true) {
            getline(cin,second_player_name);
            if (second_player_name.empty()) {
                cout << "Name cannot be empty. Please enter a valid name: ";
            }
            else {
                break;
            }
        }
        players[1] = new ultimate_tic_tac_toe_player<char>(second_player_name, 'O');
    }
    else {
        players[1] = new ultimate_tic_tac_toe_random_player<char>('O');
    }

    GameManager<char> four_in_row_game(B, players);
    four_in_row_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }


}

void runPyramidTicTacToe() {
    int choice;
    Player<char>* players[2];
    PyramidTicTacToe_Board<char>* B = new PyramidTicTacToe_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Pyramid Tic Tac Toe game!\n";

    cout << "Enter Player X name: ";
    while (true) {
        getline(cin, playerXName);
        if (playerXName.empty()) {
            cout << "Name cannot be empty. Please enter a valid name: ";
        }
        else {
            break;
        }
    }

    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    while (true) {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 for Human or 2 for Random Computer: ";
        }
        else {
            break;
        }
    }

    cin.ignore();

    if (choice == 1) {
        players[0] = new PyramidTicTacToe_Player<char>(playerXName, 'X');
    }
    else {
        players[0] = new PyramidTicTacToe_RandomPlayer<char>('X');
    }

    cout << "Enter Player 2 name: ";
    while (true) {
        getline(cin, player2Name);
        if (player2Name.empty()) {
            cout << "Name cannot be empty. Please enter a valid name: ";
        }
        else {
            break;
        }
    }

    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    while (true) {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 for Human or 2 for Random Computer: ";
        }
        else {
            break;
        }
    }

    cin.ignore();

    if (choice == 1) {
        players[1] = new PyramidTicTacToe_Player<char>(player2Name, 'O');
    }
    else {
        players[1] = new PyramidTicTacToe_RandomPlayer<char>('O');
    }

    GameManager<char> PyramidTicTacToe_game(B, players);
    PyramidTicTacToe_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}

void runWordTicTacToe() {
    set<string> dictionary = loadDictionary("dictionary.txt");

    string player1Name, player2Name;
    int player1Type, player2Type;

    cout << "Welcome to Word Tic Tac Toe game!\n";

    while (true) {
        cout << "Enter name for Player 1: ";
        getline(cin, player1Name);
        if (!player1Name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Enter name for Player 2: ";
        getline(cin, player2Name);
        if (!player2Name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose " << player1Name << ":\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player1Type;

        if (cin.fail() || (player1Type != 1 && player1Type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    cin.ignore();

    while (true) {
        cout << "Choose " << player2Name << ":\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player2Type;

        if (cin.fail() || (player2Type != 1 && player2Type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    cin.ignore();

    WordTicTacToeBoard<char> board(3, 3);
    bool isPlayer1Turn = true;
    int moveCount = 0;

    RandomWordTicTacToePlayer<char> computerPlayer('A');
    computerPlayer.boardPtr = &board;

    while (moveCount < 9) {
        board.displayBoard();

        if (isPlayer1Turn) {
            if (player1Type == 2) {
                cout << player1Name << ", the computer is making its move\n";
                int row, col;
                char letter = computerPlayer.getRandomLetter();
                computerPlayer.getmove(row, col);
                board.makeMove(row, col, letter);
            }
            else {
                cout << player1Name << ", it's your turn.\n";
                int row, col;
                char letter;

                while (true) {
                    cout << "Enter your move (row col letter): ";
                    cin >> row >> col >> letter;

                    if (row >= 0 && row < 3 && col >= 0 && col < 3 && isalpha(letter)) {
                        letter = toupper(letter);
                        if (board.makeMove(row, col, letter)) {
                            break;
                        }
                        else {
                            cout << "Cell is full. Please try again." << endl;
                        }
                    }
                    else {
                        cout << "Invalid input. Please enter row, col, and a valid letter (A-Z)." << endl;
                    }
                }
            }
        }
        else {
            if (player2Type == 2) {
                cout << player2Name << ", the computer is making its move\n";
                int row, col;
                char letter = computerPlayer.getRandomLetter();
                computerPlayer.getmove(row, col);
                board.makeMove(row, col, letter);
            }
            else {
                cout << player2Name << ", it's your turn.\n";
                int row, col;
                char letter;

                while (true) {
                    cout << "Enter your move (row col letter): ";
                    cin >> row >> col >> letter;

                    if (row >= 0 && row < 3 && col >= 0 && col < 3 && isalpha(letter)) {
                        letter = toupper(letter);
                        if (board.makeMove(row, col, letter)) {
                            break;
                        }
                        else {
                            cout << "Cell is full. Please try again." << endl;
                        }
                    }
                    else {
                        cout << "Invalid input. Please enter row, col, and a valid letter (A-Z)." << endl;
                    }
                }
            }
        }

        moveCount++;

        if (board.is_win(dictionary)) {
            board.displayBoard();
            cout << (isPlayer1Turn ? player1Name : player2Name) << " wins!" << endl;
            return;
        }

        isPlayer1Turn = !isPlayer1Turn;
    }

}

void runFourInRow() {
    int choice;
    int rows = 6;
    int columns = 7;
    Player<char>* players[2];
    four_in_row_board<char>* B = new four_in_row_board<char>();
    string first_player_name, second_player_name;

    cout << "Welcome to Four in a row!\n";

    auto get_valid_choice = [](const string& prompt) {
        int choice;
        while (true) {
            cout << prompt;
            cin >> choice;

            if (cin.fail() || (choice < 1 || choice > 2)) {
                cout << "Invalid input. Please enter 1 or 2.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            }
        }
        };

    choice = get_valid_choice("Choose first player type:\n1. Human\n2. Random Computer\n");
    switch (choice) {
    case 1:
        cout << "Enter first player name: ";
        getline(cin, first_player_name);
        players[0] = new four_in_row_Player<char>(first_player_name, 'X');
        break;
    case 2:
        players[0] = new four_in_row_Random_Player<char>('X');
        break;
    }

    choice = get_valid_choice("Choose second Player type:\n1. Human\n2. Random Computer\n");
    switch (choice) {
    case 1:
        cout << "Enter second Player name: ";
        getline(cin, second_player_name);
        players[1] = new four_in_row_Player<char>(second_player_name, 'O');
        break;
    case 2:
        players[1] = new four_in_row_Random_Player<char>('O');
        break;
    }

    GameManager<char> four_in_row_game(B, players);
    four_in_row_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void runTicTacToe4x4() {
    cout << "Welcome to 4x4 Tic Tac Toe!\n";

    char player1_symbol = 'X', player2_symbol = 'O';
    string player1_name, player2_name;
    int player1_type, player2_type;

    while (true) {
        cout << "Enter name for Player 1: ";
        getline(cin, player1_name);
        if (!player1_name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose the player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player1_type;
        cin.ignore();

        if (cin.fail() || (player1_type != 1 && player1_type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter name for Player 2: ";
        getline(cin, player2_name);
        if (!player2_name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose the player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player2_type;
        cin.ignore();

        if (cin.fail() || (player2_type != 1 && player2_type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    TicTacToe4x4Board<char> board;
    Player<char>* players[2];

    if (player1_type == 1) {
        players[0] = new TicTacToe4x4Player<char>(player1_name, player1_symbol);
    }
    else {
        players[0] = new TicTacToe4x4RandomPlayer<char>(player1_symbol, player1_name);
    }

    if (player2_type == 1) {
        players[1] = new TicTacToe4x4Player<char>(player2_name, player2_symbol);
    }
    else {
        players[1] = new TicTacToe4x4RandomPlayer<char>(player2_symbol, player2_name);
    }

    players[0]->setBoard(&board);
    players[1]->setBoard(&board);

    GameManager<char> gameManager(&board, players);
    gameManager.run();

    delete players[0];
    delete players[1];
}

void runTicTacToe5x5() {
    cout << "Welcome to 5x5 Tic Tac Toe!\n";

    char player1_symbol = 'X', player2_symbol = 'O';
    string player1_name, player2_name;
    int player1_type, player2_type;

    while (true) {
        cout << "Enter name for Player 1: ";
        getline(cin, player1_name);
        if (!player1_name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose the player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player1_type;
        cin.ignore();

        if (cin.fail() || (player1_type != 1 && player1_type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter name for Player 2: ";
        getline(cin, player2_name);
        if (!player2_name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose the player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player2_type;
        cin.ignore();

        if (cin.fail() || (player2_type != 1 && player2_type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    TicTacToe5x5Board<char> board;
    Player<char>* players[2];

    if (player1_type == 1) {
        players[0] = new TicTacToe5x5Player<char>(player1_name, player1_symbol);
    } else {
        players[0] = new TicTacToe5x5RandomPlayer<char>(player1_symbol, player1_name);
    }

    if (player2_type == 1) {
        players[1] = new TicTacToe5x5Player<char>(player2_name, player2_symbol);
    } else {
        players[1] = new TicTacToe5x5RandomPlayer<char>(player2_symbol, player2_name);
    }

    players[0]->setBoard(&board);
    players[1]->setBoard(&board);

    GameManager<char> gameManager(&board, players);
    gameManager.run();

    delete players[0];
    delete players[1];
}

void runMisereTicTacToe() {
    cout << "Welcome to Misere Tic Tac Toe!\n";

    char player1_symbol = 'X', player2_symbol = 'O';
    string player1_name, player2_name;
    int player1_type, player2_type;

    while (true) {
        cout << "Enter name for Player 1: ";
        getline(cin, player1_name);
        if (!player1_name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose the player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player1_type;
        cin.ignore();

        if (cin.fail() || (player1_type != 1 && player1_type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter name for Player 2: ";
        getline(cin, player2_name);
        if (!player2_name.empty()) {
            break;
        }
        else {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
    }

    while (true) {
        cout << "Choose the player's type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> player2_type;
        cin.ignore();

        if (cin.fail() || (player2_type != 1 && player2_type != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            break;
        }
    }

    MisereTicTacToeBoard<char> board;
    Player<char>* players[2];

    if (player1_type == 1) {
        players[0] = new MisereTicTacToePlayer<char>(player1_name, player1_symbol);
    }
    else {
        players[0] = new MisereTicTacToeRandomPlayer<char>(player1_symbol, player1_name);
    }

    if (player2_type == 1) {
        players[1] = new MisereTicTacToePlayer<char>(player2_name, player2_symbol);
    }
    else {
        players[1] = new MisereTicTacToeRandomPlayer<char>(player2_symbol, player2_name);
    }

    players[0]->setBoard(&board);
    players[1]->setBoard(&board);

    GameManager<char> gameManager(&board, players);
    gameManager.run();

    if (board.has_three_in_a_row('X')) {
        cout << player1_name << " loses!\n";
    }
    else if (board.has_three_in_a_row('O')) {
        cout << player2_name << " loses!\n";
    }
    else {
        cout << "It's a draw!\n";
    }

    delete players[0];
    delete players[1];
}

void runNumericalTicTacToe() {
    cout << "Welcome to Numerical Tic Tac Toe!\n";
    cout << "1. Player1 takes odd numbers (1, 3, 5, 7, 9).\n";
    cout << "2. Player2 takes even numbers (2, 4, 6, 8).\n";
    cout << "\nSelect a mode:\n";
    cout << "1. Play with a friend.\n";
    cout << "2. Play against the computer.\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter Player 1's name: ";
        string player1Name;
        cin >> player1Name;

        cout << "Enter Player 2's name: ";
        string player2Name;
        cin >> player2Name;

        numericalboard board;
        numericalPlayer player1(player1Name, 'o');
        numericalPlayer player2(player2Name, 'e');

        player1.setBoard(&board);
        player2.setBoard(&board);

        Player<char>* players[] = {&player1, &player2};
        GameManager<char> gameManager(&board, players);

        gameManager.run();

    } else if (choice == 2) {
        cout << "Enter your name: ";
        string playerName;
        cin >> playerName;

        cout << "Choose your type:\n";
        cout << "1. Odd numbers (1, 3, 5, 7, 9).\n";
        cout << "2. Even numbers (2, 4, 6, 8).\n";
        cout << "Choice: ";

        int type;
        cin >> type;

        if (type == 1) {
            numericalboard board;
            numericalPlayer player(playerName, 'o');
            numericalRandomPlayer computer("Computer", board);

            player.setBoard(&board);
            computer.setBoard(&board);

            Player<char>* players[] = {&player, &computer};
            GameManager<char> gameManager(&board, players);

            gameManager.run();

        } else if (type == 2) {
            numericalboard board;
            numericalPlayer player(playerName, 'e');
            numericalRandomPlayer computer("Computer", board);

            player.setBoard(&board);
            computer.setBoard(&board);

            Player<char>* players[] = {&computer, &player};
            GameManager<char> gameManager(&board, players);

            gameManager.run();

        } else {
            cout << "Invalid choice. Restart the game.\n";
        }

    } else {
        cout << "Invalid choice. Please restart the game and select a valid option.\n";
    }
}

int main() {
    int gameChoice;

    do {
        cout << "\nWelcome to the Game Menu! Choose a game:\n";
        cout << "1. Pyramid Tic-Tac-Toe\n";
        cout << "2. Four-in-Row\n";
        cout << "3. 5x5 Tic-Tac-Toe\n";
        cout << "4. Word Tic-Tac-Toe\n";
        cout << "5. Numerical Tic-Tac-Toe\n";
        cout << "6. Misere Tic-Tac-Toe\n";
        cout << "7. 4x4 Tic-Tac-Toe\n";
        cout << "8. Ultimate Tic-Tac-Toe\n";
        cout << "9. SUS\n";
        cout << "10.Exit\n";

        cout << "Enter your choice: ";
        cin >> gameChoice;

        switch (gameChoice) {
            case 1:
                cin.ignore();
                runPyramidTicTacToe();
                break;
            case 2:
                runFourInRow();
                break;
            case 3:
                cin.ignore();
                runTicTacToe5x5();
                break;
            case 4:
                cin.ignore();
                runWordTicTacToe();
                break;
            case 5:
                runNumericalTicTacToe();
                break;
            case 6:
                cin.ignore();
                runMisereTicTacToe();
                break;
            case 7:
                cin.ignore();
                runTicTacToe4x4();
                break;
            case 8:
                runUltimateTicTacToe();
            case 9:
                srand(time(0));
                runSUSGame();
            case 10:
                cout << "Exiting the game. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    } while (gameChoice != 10);

    return 0;
}