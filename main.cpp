#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib> // For srand
#include <ctime>   // For time

// Include both the original framework and your new game classes
#include "BoardGame_Classes.h"
#include "XO_Classes.h" 
#include "Numerical_TTT_Classes.h" // Your new file

using namespace std;

// Function to run the X-O game (copied from original XO_Demo.cpp)
void run_xo_game() {
    UI<char>* game_ui = new XO_UI();
    Board<char>* xo_board = new X_O_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();

    // Cleanup
    delete xo_board;
    delete game_ui;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
}

// Function to run your new Numerical TTT game
void run_numerical_ttt_game() {
    UI<int>* game_ui = new Numerical_TTT_UI();
    Board<int>* game_board = new Numerical_TTT_Board();
    Player<int>** players = game_ui->setup_players();
    GameManager<int> game(game_board, players, game_ui);
    game.run();

    // Cleanup
    delete game_board;
    delete game_ui;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    int choice = 0;
    while (choice != 3) {
        cout << "\n--- OOP Game Arcade Menu ---" << endl;
        cout << "1. Play Numerical Tic-Tac-Toe (Group Game 9)" << endl;
        cout << "2. Play X-O (Demo)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            run_numerical_ttt_game();
        }
        else if (choice == 2) {
            run_xo_game();
        }
        else if (choice == 3) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0; // Exit successfully
}