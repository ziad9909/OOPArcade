#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <cstdlib> // For srand
#include <ctime>   // For time

#include "BoardGame_Classes.h"
#include "XO_Classes.h" 
#include "Numerical_TTT_Classes.h"
#include "Misere_TTT_Classes.h"

using namespace std;

// Function declarations
void run_xo_game();
void run_numerical_ttt_game();
void run_misere_ttt_game();

// Function to run the X-O game
void run_xo_game() {
    UI<char>* game_ui = new XO_UI();
    Board<char>* xo_board = new X_O_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();

    // Cleanup - safe order
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
    delete xo_board;
}

// Function to run Numerical TTT game
void run_numerical_ttt_game() {
    UI<int>* game_ui = new Numerical_TTT_UI();
    Board<int>* game_board = new Numerical_TTT_Board();
    Player<int>** players = game_ui->setup_players();
    GameManager<int> game(game_board, players, game_ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
    delete game_board;
}


// Function to run Misere TTT
void run_misere_ttt_game() {
    UI<char>* game_ui = new Misere_TTT_UI();
    Board<char>* game_board = new Misere_TTT_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(game_board, players, game_ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
    delete game_board;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    int choice = 0;
    while (true) {
        cout << "\n--- OOP Game Arcade Menu ---" << endl;
        cout << "1. Play Numerical Tic-Tac-Toe (Group Game 9)" << endl;
        cout << "2. Play X-O (Demo)" << endl;
        cout << "3. Play 5x5 Tic-Tac-Toe" << endl;
        cout << "4. Play Misere Tic Tac Toe" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            run_numerical_ttt_game();
            break;
        case 2:
            run_xo_game();
            break;
        case 4:
            run_misere_ttt_game();
            break;
        case 5:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}