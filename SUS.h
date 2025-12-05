/**
 * @file SUS.h
 * @brief SUS Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief SUS Tic-Tac-Toe: Players create 'SUS' sequences for points.
 *
 * @game
 * - Board: 3x3 grid
 * - Players: 2 (Player 'S' and Player 'U')
 * - Objective: Create 'SUS' sequences for points
 * - Sequences: Any row, column, or diagonal that spells "SUS"
 * - Points accumulate throughout the game
 * - Winner has more points when board is full
 *
 * @variant
 * - Word-based scoring system
 * - Players score for creating 'SUS' patterns
 * - Multiple 'SUS' sequences can be created
 * - Strategic placement to maximize 'SUS' creation
 */

#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class SUS_board
 * @brief Class representing SUS Tic-Tac-Toe board
 *
 * Handles board state, moves, score calculation, win/draw checking,
 * and AI logic using minimax with alpha-beta pruning.
 */
class SUS_board : public Board<char> {
public:
    /**
     * @brief Constructor initializes empty 3x3 board and scores
     */
    SUS_board();

    /**
     * @brief Update board with a move
     * @param move Pointer to Move object
     * @return true if move is valid and placed, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to Player object
     * @return true if player has more points than opponent, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to Player object
     * @return true if player has fewer points than opponent, false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game ended in draw
     * @param player Pointer to Player object
     * @return true if scores are equal when board is full, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game board is full
     * @param player Pointer to Player object
     * @return true if board is full, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Get current score of player
     * @param player Pointer to Player object
     * @return Player's current score
     */
    int get_score(Player<char>* player);

    /**
     * @brief Check new SUS sequences completed by last move
     * @param x Row index of last move
     * @param y Column index of last move
     * @return Number of new SUS sequences completed
     */
    int check_new_sequences(int x, int y);

    // ===================== AI FUNCTIONS =====================

    /**
     * @brief Get vector of empty cells on board
     * @return Vector of (row, column) pairs for empty cells
     */
    vector<pair<int, int>> get_empty_cells();

    /**
     * @brief Evaluate board state from AI perspective
     * @param aiSymbol AI player's symbol
     * @return Evaluation score
     */
    int evaluate_state(char aiSymbol);

    /**
     * @brief Minimax algorithm with alpha-beta pruning
     * @param depth Current depth of recursion
     * @param maximizing True if AI's turn, false if human's turn
     * @param aiSymbol Symbol of AI player ('S' or 'U')
     * @param humanSymbol Symbol of human player
     * @param alpha Alpha value for pruning
     * @param beta Beta value for pruning
     * @return Evaluated score for current board state
     */
    int minimax(int depth, bool maximizing, char aiSymbol, char humanSymbol, int alpha, int beta);

    /**
     * @brief Find best move for AI using minimax
     * @param aiSymbol AI player's symbol
     * @param humanSymbol Human player's symbol
     * @return (row, column) pair representing best move
     */
    pair<int, int> get_best_move(char aiSymbol, char humanSymbol);

private:
    char blank_symbol = '.';   ///< Symbol for empty cell
    int score_S = 0;           ///< Accumulated score for player S
    int score_U = 0;           ///< Accumulated score for player U
};

/**
 * @class SUS_player
 * @brief Handles player setup and moves (Human or AI) for SUS game
 */
class SUS_player : public UI<char> {
public:
    /**
     * @brief Constructor initializes UI
     */
    SUS_player();

    /**
     * @brief Destructor
     */
    ~SUS_player();

    /**
     * @brief Create a new player
     * @param name Name of player
     * @param symbol Player's symbol ('S' or 'U')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Set up two players
     * @return Array of pointers to Player objects
     */
    Player<char>** setup_players() override;

    /**
     * @brief Get next move from player
     * @param player Pointer to Player object making move
     * @return Pointer to Move object representing chosen move
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif