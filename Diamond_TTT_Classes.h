/**
 * @file Diamond_TTT_Classes.h
 * @brief Diamond Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Diamond Tic-Tac-Toe: Played on a diamond-shaped 5x5 grid.
 *
 * @game
 * - Board: 5x5 diamond-shaped grid (13 playable cells)
 * - Players: 2
 * - Objective: Simultaneously complete a line of 3 and a line of 4 marks
 * - Lines can be horizontal, vertical, or diagonal
 * - The two winning lines must be in different directions
 * - Lines can share one common mark
 *
 * @variant
 * - Unique diamond-shaped board pattern
 * - Dual winning condition requirement
 * - Strategic blocking of opponent's potential lines
 */

#ifndef DIAMOND_TTT_CLASSES_H
#define DIAMOND_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <map>
#include <string>
#include <limits>

using namespace std;

/**
 * @class Diamond_TTT_Board
 * @brief Board class for Diamond Tic-Tac-Toe game
 *
 * Implements a 5x5 diamond-shaped grid with special winning conditions.
 */
class Diamond_TTT_Board : public Board<char> {
private:
    vector<pair<int, int>> valid_cells; ///< Coordinates of valid diamond-shaped cells

    /**
     * @brief Get cells along a line
     * @param start_x Starting X coordinate
     * @param start_y Starting Y coordinate
     * @param dx X direction increment
     * @param dy Y direction increment
     * @param length Length of line
     * @return Vector of cell coordinates along the line
     */
    vector<pair<int, int>> get_line_cells(int start_x, int start_y, int dx, int dy, int length);

    /**
     * @brief Check if coordinate is within diamond shape
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if cell is part of diamond shape, false otherwise
     */
    bool is_valid_cell(int x, int y) const;

    /**
     * @brief Get all possible winning lines in the diamond
     * @return Vector of all possible winning lines
     */
    vector<vector<pair<int, int>>> get_all_lines();

    /**
     * @brief Evaluate board state for AI
     * @param board Pointer to game board
     * @param ai_symbol AI player's symbol
     * @param opponent_symbol Opponent's symbol
     * @return Evaluation score
     */
    int evaluate_board(Diamond_TTT_Board* board, char ai_symbol, char opponent_symbol);

    /**
     * @brief Get direction of a line
     * @param line Vector of cell coordinates
     * @return String indicating line direction
     */
    string get_line_direction(const vector<pair<int, int>>& line);

public:
    /**
     * @brief Constructor for Diamond Tic-Tac-Toe board
     * Initializes 5x5 board with diamond pattern
     */
    Diamond_TTT_Board();

    /**
     * @brief Update board with a player's move
     * @param move Pointer to Move object containing position and symbol
     * @return true if move is valid and applied, false otherwise
     */
    virtual bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won according to diamond TTT rules
     * @param player Pointer to the player to check
     * @return true if player has won, false otherwise
     */
    virtual bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to the player to check
     * @return false - not used in this symmetric game
     */
    virtual bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player to check
     * @return true if all valid cells filled with no winner
     */
    virtual bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to the player to check
     * @return true if game is won or drawn, false otherwise
     */
    virtual bool game_is_over(Player<char>* player) override;

    /**
     * @brief Validate if a move is valid
     * @param x Row coordinate (0-4)
     * @param y Column coordinate (0-4)
     * @return Empty string if valid, error message if invalid
     */
    string validate_move(int x, int y) const;

    /**
     * @brief Get list of empty cells
     * @return Vector of empty cell coordinates
     */
    vector<pair<int, int>> get_empty_cells() const;

    /**
     * @brief Debug method to check winning conditions
     * @param player Pointer to player to debug
     */
    void debug_win_check(Player<char>* player);

    /**
     * @brief Undo a move
     * @param x Row coordinate
     * @param y Column coordinate
     */
    void undo_move(int x, int y);
};

/**
 * @class Diamond_TTT_UI
 * @brief User Interface for Diamond Tic-Tac-Toe
 *
 * Handles player input/output, displays board, and manages player setup
 */
class Diamond_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor with welcome message
     */
    Diamond_TTT_UI();

    /**
     * @brief Set up two players for the game
     * @return Array of two Player pointers
     */
    virtual Player<char>** setup_players() override;

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Display the board with diamond shape
     * @param matrix Board matrix to display
     */
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const;

private:
    /**
     * @brief Evaluate board state for AI
     * @param board Pointer to game board
     * @param ai_symbol AI player's symbol
     * @param opponent_symbol Opponent's symbol
     * @return Evaluation score
     */
    int evaluate_board(Diamond_TTT_Board* board, char ai_symbol, char opponent_symbol);

    /**
     * @brief Minimax recursive function
     */
    int minimax(Diamond_TTT_Board* board,
        char current_symbol,
        char ai_symbol,
        char opponent_symbol,
        bool isMaximizing,
        int depth = 0);

    int minimax_helper(Diamond_TTT_Board* board,
        char current_symbol,
        char ai_symbol,
        char opponent_symbol,
        bool isMaximizing,
        int depth);

    /**
     * @brief Find best move for AI
     * @param board Pointer to game board
     * @param ai_symbol AI player's symbol
     * @param opponent_symbol Opponent's symbol
     * @return Pair of coordinates for best move
     */
    pair<int, int> find_best_move(Diamond_TTT_Board* board, char ai_symbol, char opponent_symbol);
};

#endif // DIAMOND_TTT_CLASSES_H