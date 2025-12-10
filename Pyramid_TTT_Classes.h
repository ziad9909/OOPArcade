/**
 * @file Pyramid_TTT_Classes.h
 * @brief Pyramid Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Pyramid Tic-Tac-Toe: A triangular board with unique winning patterns.
 *
 * @game
 * - Board: Pyramid-shaped grid (3 rows: 1, 2, 3 cells)
 * - Players: 2
 * - Symbols: 'X' and 'O'
 * - Objective: Get three in a row (horizontal, diagonal, or special patterns)
 * - Total cells: 6 (1 + 2 + 3)
 * - Unique pyramid structure creates new strategic possibilities
 *
 * @variant
 * - Non-rectangular board shape
 * - Limited cell count (6 total)
 * - Asymmetric winning patterns
 * - Quick gameplay with high strategic depth
 * - Special diagonal and edge winning combinations
 *
 * @strategy
 * - Control the apex (top cell) for maximum influence
 * - Watch for diagonal threats across pyramid levels
 * - Base row control is crucial for defensive play
 */

#ifndef PYRAMID_TTT_CLASSES_H
#define PYRAMID_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

/**
 * @class Pyramid_TTT_Board
 * @brief Board class for Pyramid Tic-Tac-Toe with triangular structure (3 levels: 1+2+3 cells)
 *
 * Implements a pyramid-shaped board with 3 levels:
 * - Level 1 (top): 1 cell
 * - Level 2 (middle): 2 cells
 * - Level 3 (bottom): 3 cells
 *
 * Players aim to get three of their symbols in a row following
 * the unique geometric patterns of the pyramid structure.
 */
class Pyramid_TTT_Board : public Board<char> {
public:
    /**
     * @brief Constructor for Pyramid Tic-Tac-Toe board
     *
     * Initializes the pyramid structure with appropriate dimensions
     * and sets all cells to empty ('_').
     */
    Pyramid_TTT_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object containing coordinates and symbol
     * @return true if move is valid and applied, false otherwise
     *
     * Validates that the target cell exists in the pyramid structure
     * and is empty before placing the symbol.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won with three in a row
     * @param player Pointer to player to check
     * @return true if player has three in a row, false otherwise
     *
     * Checks all possible winning patterns:
     * - Horizontal lines within each level
     * - Diagonal patterns across levels
     * - Special pyramid-specific combinations
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return false - not used in this game variant
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Check if game is a draw
     * @param player Pointer to player to check
     * @return true if all 6 cells are filled with no winner, false otherwise
     *
     * A draw occurs when the pyramid is completely filled and
     * neither player has achieved three in a row.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if game is won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    

    int evaluate_state(char aiSym, char huSym, int depth);

    int minimax(bool isMax, char aiSym, char huSym, int depth, int alpha, int beta);

    Move<char>* get_best_move_for_ai(char aiSym, char huSym);
};

/**
 * @class Pyramid_TTT_UI
 * @brief User Interface for Pyramid Tic-Tac-Toe with visual pyramid display
 *
 * Handles player input, board display, and manages interaction
 * with the pyramid structure. Displays the board in a visually
 * appealing pyramid format.
 */
class Pyramid_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Pyramid Tic-Tac-Toe UI
     *
     * Initializes the UI with win condition of 3 in a row.
     */
    Pyramid_TTT_UI() : UI<char>(3) {}

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object containing coordinates and symbol
     *
     * Prompts the player to enter valid coordinates within
     * the pyramid structure.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

/**
 * @class RandomComputerPlayer
 * @brief AI player making random valid moves in Pyramid Tic-Tac-Toe
 *
 * Implements a simple computer opponent that randomly selects
 * empty cells on the pyramid board. Useful for testing and
 * casual gameplay against AI.
 */
class RandomComputerPlayer : public Player<char> {
public:
    /**
     * @brief Constructor for random computer player
     * @param name Computer player's name
     * @param symbol Computer player's symbol ('X' or 'O')
     *
     * Creates a computer-controlled player that will make
     * random valid moves during gameplay.
     */
    RandomComputerPlayer(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER) {}

    /**
     * @brief Generate a random valid move for the computer player
     * @return Pointer to Move object with random valid coordinates
     *
     * Randomly searches for empty cells ('_') on the board
     * and returns a move to place the computer's symbol there.
     * Continues searching until a valid empty cell is found.
     */
    Move<char>* get_computer_move() {
        Board<char>* board = this->get_board_ptr();
        while (true) {
            int x = rand() % board->get_rows();
            int y = rand() % board->get_columns();
            if (board->get_cell(x, y) == '_') {
                return new Move<char>(x, y, this->symbol);
            }
        }
    }
};
class MinimaxComputerPlayer : public Player<char> {
public:
    MinimaxComputerPlayer(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER) {}

    Move<char>* get_computer_move();
};

#endif