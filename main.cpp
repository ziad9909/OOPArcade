/**
 * @file main.cpp
 * @brief Main entry point for OOP Game Arcade application
 * @author CS213 Assignment 3 Team
 * @date December 2025
 *
 * This file contains the main menu system that allows users to select and play
 * different Tic-Tac-Toe game variants. It integrates all game implementations
 * and provides a unified interface.
 *
 * Available Games:
 * 1. Numerical Tic-Tac-Toe (Group Game 9)
 * 2. Classic X-O (Demo)
 * 3. Misère Tic-Tac-Toe
 * 4. SUS
 * 5. Word Tic-Tac-Toe
 * 6. 4x4 Moving Tic-Tac-Toe
 * 7. Obstacle Tic-Tac-Toe
 * 8. Infinity Tic-Tac-Toe
 * 9. Four-in-a-Row (Connect 4)
 * 10. Diamond Tic-Tac-Toe
 * 11. 5x5 Tic-Tac-Toe
 */

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
#include "SUS.h"
#include "Word_TTT.h"
#include "4x4_TTT_Classes.h"
#include "Obstacle6x6_TTT.h"
#include "Timed_TTT_Classes.h"
#include "Four_in_a_row.h"
#include "Diamond_TTT_Classes.h"
#include "FiveByFiveTTT_Classes.h"

using namespace std;

// Function declarations

/**
 * @brief Runs the classic X-O (Tic-Tac-Toe) game
 * @details Creates board, UI, sets up players, and starts the game manager
 */
void run_xo_game();

/**
 * @brief Runs the Numerical Tic-Tac-Toe game
 * @details Players use numbers (odd vs even) trying to sum to 15
 */
void run_numerical_ttt_game();

/**
 * @brief Runs the Misère Tic-Tac-Toe game
 * @details Inverse game where the goal is to force opponent to get three in a row
 */
void run_misere_ttt_game();

/**
 * @brief Runs the SUS game
 * @details Players place S or U trying to complete "S-U-S" sequences
 */
void run_SUS();

/**
 * @brief Runs the Word Tic-Tac-Toe game
 * @details Players place letters trying to form valid 3-letter words
 */
void run_word_ttt_game();

/**
 * @brief Runs the 4x4 Moving Tic-Tac-Toe game
 * @details Players move their tokens on a 4x4 board trying to align three
 */
void run_4x4_ttt_game();

/**
 * @brief Runs the Obstacle 6x6 Tic-Tac-Toe game
 * @details Random obstacles appear every round, players need 4 in a row
 */
void run_obstacle6x6_ttt_game();

/**
 * @brief Runs the Infinity (Timed) Tic-Tac-Toe game
 * @details Oldest moves disappear after every 3 moves
 */
void run_timed_ttt_game();

/**
 * @brief Runs the Four-in-a-Row (Connect 4) game
 * @details Gravity-based game on 6x7 board, need 4 in a row
 */
void run_Four_in_row();

/**
 * @brief Runs the Diamond Tic-Tac-Toe game
 * @details Play on diamond-shaped board, need simultaneous 3-line and 4-line
 */
void run_diamond_ttt_game();

/**
 * @brief Runs the 5x5 Tic-Tac-Toe game
 * @details Score-based game, player with most 3-in-a-row sequences wins
 */
void run_fivebyfive_ttt_game();

// Function implementations

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

void run_SUS() {
    UI<char>* game_ui = new SUS_player();
    SUS_board* game_board = new SUS_board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(game_board, players, game_ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
    delete game_board;
}

void run_word_ttt_game() {
    UI<char>* game_ui = new Word_TTT_UI();
    Board<char>* game_board = new Word_TTT_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(game_board, players, game_ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
    delete game_board;
}

void run_4x4_ttt_game() {
    UI<char>* ui = new FourByFour_TTT_UI();
    Board<char>* board = new FourByFour_TTT_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    delete board;
    delete ui;
}

void run_obstacle6x6_ttt_game() {
    UI<char>* ui = new Obstacle6x6_TTT_UI();
    Board<char>* board = new Obstacle6x6_TTT_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    delete board;
}

void run_timed_ttt_game() {
    UI<char>* ui = new Timed_TTT_UI();
    Board<char>* board = new Timed_TTT_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    delete board;
}

void run_Four_in_row() {
    UI<char>* ui = new Four_in_a_row_Ui;
    Board<char>* board = new Four_in_a_row_board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    delete board;
}

void run_diamond_ttt_game() {
    UI<char>* ui = new Diamond_TTT_UI();
    Board<char>* board = new Diamond_TTT_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    delete board;
}

void run_fivebyfive_ttt_game() {
    FiveByFive_TTT_UI* ui = new FiveByFive_TTT_UI();
    FiveByFive_TTT_Board* board = new FiveByFive_TTT_Board();
    Player<char>** players = ui->setup_players();

    // Set board pointers for both players
    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);

    // Use custom game loop that only ends after 24 moves
    ui->run_game_with_custom_loop(board, players);

    // Cleanup
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    delete board;
}

/**
 * @brief Main function - entry point of the application
 * @return 0 on successful exit
 *
 * Displays a menu allowing users to select which game to play.
 * Loops until user chooses to exit.
 */
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    int choice = 0;
    while (true) {
        cout << "\n--- OOP Game Arcade Menu ---" << endl;
        cout << "1. Play Numerical Tic-Tac-Toe (Group Game 9)" << endl;
        cout << "2. Play X-O (Demo)" << endl;
        cout << "3. Play Misere Tic Tac Toe" << endl;
        cout << "4. Play SUS" << endl;
        cout << "5. Play Word Tic Tac Toe" << endl;
        cout << "6. Play 4x4 Moving Tic-Tac-Toe" << endl;
        cout << "7. Play Obstacle Tic Tac Toe" << endl;
        cout << "8. Play Infinity Tic Tac Toe" << endl;
        cout << "9. Play Four in a Row" << endl;
        cout << "10. Play Diamond Tic Tac Toe" << endl;
        cout << "11. Play 5x5 Tic Tac Toe" << endl;
        cout << "12. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            run_numerical_ttt_game();
            break;
        case 2:
            run_xo_game();
            break;
        case 3:
            run_misere_ttt_game();
            break;
        case 4:
            run_SUS();
            break;
        case 5:
            run_word_ttt_game();
            break;
        case 6:
            run_4x4_ttt_game();
            break;
        case 7:
            run_obstacle6x6_ttt_game();
            break;
        case 8:
            run_timed_ttt_game();
            break;
        case 9:
            run_Four_in_row();
            break;
        case 10:
            run_diamond_ttt_game();
            break;
        case 11:
            run_fivebyfive_ttt_game();
            break;
        case 12:
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