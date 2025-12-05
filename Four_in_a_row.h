/**
 * @file Four_in_a_row.h
 * @brief Connect Four (Four-in-a-Row) implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Connect Four: Drop discs to get four in a row.
 *
 * @game
 * - Board: 6 rows x 7 columns grid
 * - Players: 2
 * - Symbols: Player 1 uses 'X', Player 2 uses 'O'
 * - Objective: Connect four of your discs in a row (horizontal, vertical, or diagonal)
 * - Gravity: Discs fall to the lowest available position in chosen column
 *
 * @variant
 * - Vertical board with gravity effect
 * - Column-based moves instead of cell-based
 * - Classic strategy game with deep gameplay
 */

#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class Four_in_a_row_board
 * @brief Represents the game board for Four-in-a-Row (Connect 4)
 *
 * Handles board updates, win/draw checking, and AI functions.
 */
class Four_in_a_row_board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol for empty cells

public:
    /**
     * @brief Constructor: Initializes 6x7 board
     */
    Four_in_a_row_board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object
     * @return true if move was successful, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to player to check
     * @return true if player has four in a row, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return false - not used in this game
     */
    bool is_lose(Player<char>* player) override { return false; };

    /**
     * @brief Check if game is a draw
     * @param player Pointer to player to check
     * @return true if board is full with no winner
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if game is won or drawn
     */
    bool game_is_over(Player<char>* player) override;

    // ---------------- AI FUNCTIONS ----------------

    /**
     * @brief Get all valid columns where a move can be made
     * @return Vector of column indices
     */
    vector<int> get_valid_columns();

    /**
     * @brief Evaluate board for AI
     * @param aiSymbol AI player's symbol
     * @return Numeric score from AI's perspective
     */
    int evaluate_board(char aiSymbol);

    /**
     * @brief Count sequences of given length for a symbol
     * @param symbol Player's symbol
     * @param length Length of sequence to check
     * @return Number of sequences of given length
     */
    int count_sequences(char symbol, int length);

    /**
     * @brief Minimax algorithm with alpha-beta pruning
     * @param depth Remaining depth to search
     * @param maximizing True if AI is maximizing, false if minimizing
     * @param aiSymbol AI player's symbol
     * @param humanSymbol Human player's symbol
     * @param alpha Alpha value for pruning
     * @param beta Beta value for pruning
     * @return Evaluated score for this board state
     */
    int minimax(int depth, bool maximizing, char aiSymbol, char humanSymbol, int alpha, int beta);

    /**
     * @brief Get best move column for AI
     * @param aiSymbol AI player's symbol
     * @param humanSymbol Human player's symbol
     * @return Column index of best move
     */
    int get_best_move(char aiSymbol, char humanSymbol);

    /**
     * @brief Check if symbol has a winning sequence
     * @param symbol Player's symbol
     * @return true if symbol has four in a row
     */
    bool check_win_for_symbol(char symbol);

    /**
     * @brief Undo last move in a column
     * @param col Column index to undo
     */
    void undo_move(int col);
};

/**
 * @class Four_in_a_row_Ui
 * @brief User interface for Four-in-a-Row game
 */
class Four_in_a_row_Ui : public UI<char> {
public:
    /**
     * @brief Constructor for Four-in-a-Row UI
     */
    Four_in_a_row_Ui();

    /**
     * @brief Destructor
     */
    ~Four_in_a_row_Ui();

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol
     * @param type Player type (Human or Computer)
     * @return Pointer to created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Set up two players for the game
     * @return Array of two player pointers
     */
    Player<char>** setup_players() override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making move
     * @return Pointer to Move object
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif //FOUR_IN_A_ROW_H