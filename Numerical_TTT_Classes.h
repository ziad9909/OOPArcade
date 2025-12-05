/**
 * @file Numerical_TTT_Classes.h
 * @brief Numerical Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Numerical Tic-Tac-Toe: Players use numbers instead of X and O.
 *
 * @game
 * - Board: 3x3 grid
 * - Players: 2
 * - Player 1: Uses odd numbers (1, 3, 5, 7, 9)
 * - Player 2: Uses even numbers (2, 4, 6, 8)
 * - Objective: Be first to have 3 numbers in a line sum to exactly 15
 * - Each number can be used only once per game
 *
 * @variant
 * - Mathematical variant of Tic-Tac-Toe
 * - Based on magic square properties
 * - Requires both strategic placement and number selection
 */

#pragma once
#ifndef NUMERICAL_TTT_CLASSES_H
#define NUMERICAL_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <numeric>

using namespace std;

/**
 * @class Numerical_TTT_Board
 * @brief Board class for Numerical Tic-Tac-Toe
 *
 * Implements Numerical Tic-Tac-Toe where players use numbers
 * and win by getting three numbers in a line that sum to 15.
 */
class Numerical_TTT_Board : public Board<int> {
private:
    vector<int> odd_nums;   ///< Available odd numbers for Player 1
    vector<int> even_nums;  ///< Available even numbers for Player 2

    /**
     * @brief Check all 8 lines for a winning sum
     * @return true if any line sums to 15, false otherwise
     */
    bool check_win();

public:
    /**
     * @brief Constructor for Numerical Tic-Tac-Toe board
     *
     * Initializes 3x3 board and number pools:
     * - Player 1 gets odd numbers: 1, 3, 5, 7, 9
     * - Player 2 gets even numbers: 2, 4, 6, 8
     */
    Numerical_TTT_Board();

    /**
     * @brief Update board with a player's move
     * @param move Pointer to Move object containing position and number
     * @return true if move is valid and applied, false otherwise
     */
    virtual bool update_board(Move<int>* move) override;

    /**
     * @brief Check if game is a draw
     * @param player Current player
     * @return true if board is full and no one has won
     */
    virtual bool is_draw(Player<int>* player) override;

    /**
     * @brief Check if player has won
     * @param player Current player
     * @return true if player has any line summing to 15
     */
    virtual bool is_win(Player<int>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Current player
     * @return false - not used in this game
     */
    virtual bool is_lose(Player<int>* player) override { return false; }

    /**
     * @brief Check if game is over
     * @param player Current player
     * @return true if game is won or drawn
     */
    virtual bool game_is_over(Player<int>* player) override;

    /**
     * @brief Get available numbers for a player
     * @param player_symbol 1 for Odd (Player 1), 2 for Even (Player 2)
     * @return Vector of available numbers
     */
    vector<int> get_available_moves(int player_symbol);
};

/**
 * @class Numerical_TTT_UI
 * @brief User Interface for Numerical Tic-Tac-Toe
 */
class Numerical_TTT_UI : public UI<int> {
public:
    /**
     * @brief Constructor for Numerical Tic-Tac-Toe UI
     */
    Numerical_TTT_UI();

    /**
     * @brief Set up two players for the game
     * @return Array of two Player pointers
     *
     * Assigns symbol '1' to Player 1 (Odd) and '2' to Player 2 (Even)
     */
    virtual Player<int>** setup_players() override;

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol (1 for odd, 2 for even)
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    virtual Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object
     */
    virtual Move<int>* get_move(Player<int>* player) override;
};

#endif // NUMERICAL_TTT_CLASSES_H