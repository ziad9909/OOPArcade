#ifndef DIAMOND_TTT_CLASSES_H
#define DIAMOND_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <set>
#include <algorithm>
#include <utility> // For std::pair
#include <map>     // For std::map
#include <string>  // For std::string

using namespace std;

/**
 * @class Diamond_TTT_Board
 * @brief Board class for Diamond Tic-Tac-Toe game
 *
 * Implements a 5x5 diamond-shaped grid with special winning conditions.
 * A player wins by simultaneously completing:
 * 1. A line of three marks
 * 2. A line of four marks
 * 3. The two lines must be in different directions
 * 4. They can share one common mark
 */
class Diamond_TTT_Board : public Board<char> {
private:
    // Store coordinates of valid diamond-shaped cells
    vector<pair<int, int>> valid_cells;

    // Helper function to get cells along a line
    vector<pair<int, int>> get_line_cells(int start_x, int start_y, int dx, int dy, int length);

    // Check if a coordinate is within the diamond shape
    bool is_valid_cell(int x, int y) const;

    // Get all possible winning lines in the diamond
    vector<vector<pair<int, int>>> get_all_lines();

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
    virtual bool update_board(Move<char>* move);

    /**
     * @brief Check if player has won according to diamond TTT rules
     * @param player Pointer to the player to check
     * @return true if player has won, false otherwise
     */
    virtual bool is_win(Player<char>* player);

    /**
     * @brief Check if player has lost (not used in this symmetric game)
     */
    virtual bool is_lose(Player<char>* player) { return false; }

    /**
     * @brief Check if game is a draw (all valid cells filled, no winner)
     */
    virtual bool is_draw(Player<char>* player);

    /**
     * @brief Check if game is over (win or draw)
     */
    virtual bool game_is_over(Player<char>* player);

    /**
     * @brief Validate if a move is valid
     * @param x Row coordinate (0-4)
     * @param y Column coordinate (0-4)
     * @return Empty string if valid, error message if invalid
     */
    string validate_move(int x, int y) const;

    /**
     * @brief Get list of empty cells (for computer AI)
     */
    vector<pair<int, int>> get_empty_cells() const;

    /**
     * @brief Debug method to check winning conditions
     */
    void debug_win_check(Player<char>* player);
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
    virtual Player<char>** setup_players();

    /**
     * @brief Create a player object
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Get a move from a player (human or computer)
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Display the board with diamond shape information
     */
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const;
};

#endif // DIAMOND_TTT_CLASSES_H