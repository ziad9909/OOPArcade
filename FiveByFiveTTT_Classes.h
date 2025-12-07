/**
 * @file FiveByFiveTTT_Classes.h
 * @brief 5x5 Tic-Tac-Toe variant implementation with Smart AI
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief 5x5 Tic-Tac-Toe: Larger board, compete for most three-in-a-rows.
 *
 * @game
 * - Board: 5x5 grid
 * - Players: 2
 * - Symbols: 'X' and 'O'
 * - Objective: Create more three-in-a-row sequences than opponent
 * - Game ends when board is full (after 25 moves)
 * - Winner is player with more sequences at game end
 *
 * @variant
 * - Larger 5x5 board for more complex gameplay
 * - Score-based winning condition
 * - Multiple winning lines can be created
 * - Draws possible when sequences are equal
 */

#pragma once
#ifndef FIVE_BY_FIVE_TTT_CLASSES_H
#define FIVE_BY_FIVE_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <limits>

using namespace std;

/**
 * @class FiveByFive_TTT_Board
 * @brief Represents 5x5 Tic-Tac-Toe board
 *
 * Players compete to create the most three-in-a-row sequences.
 */
class FiveByFive_TTT_Board : public Board<char> {
private:
    /**
     * @brief Count all three-in-a-row sequences for given symbol
     * @param symbol Symbol to check ('X' or 'O')
     * @return Total number of three-in-a-row sequences
     */
    int count_sequences(char symbol);

public:
    /**
     * @brief Constructor for 5x5 Tic-Tac-Toe board
     */
    FiveByFive_TTT_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object
     * @return true if move is valid and applied, false otherwise
     */
    virtual bool update_board(Move<char>* move) override;

    /**
     * @brief Check if game is a draw
     * @param player Current player
     * @return true if board is full, false otherwise
     */
    virtual bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if player has won
     * @param player Current player to check
     * @return true if player has more sequences than opponent
     */
    virtual bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Current player to check
     * @return true if opponent has more sequences
     */
    virtual bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Current player
     * @return true if board is full (after 25 moves)
     */
    virtual bool game_is_over(Player<char>* player) override;

    /**
     * @brief Get sequence counts for both players
     * @return Pair (X sequences, O sequences)
     */
    pair<int, int> get_sequence_counts();

    /**
     * @brief Get number of moves made
     * @return Current move count
     */
    int get_move_count() const { return n_moves; }

    /**
     * @brief Count potential sequences (2 in a row with empty space)
     * @param symbol Symbol to check
     * @return Number of potential sequences
     */
    int count_potential_sequences(char symbol);
};

// AI Helper Functions (instead of SmartAI class)

/**
 * @brief Evaluate board position with advanced heuristics
 * @param board Current board state
 * @param ai_symbol AI's symbol
 * @param opponent_symbol Opponent's symbol
 * @param depth Current depth (for dynamic evaluation)
 * @return Score (positive favors AI, negative favors opponent)
 */
int evaluate_board_ai(FiveByFive_TTT_Board* board, char ai_symbol, char opponent_symbol, int depth);

/**
 * @brief Minimax algorithm with alpha-beta pruning
 * @param board Current board state
 * @param depth Current search depth
 * @param alpha Alpha value for pruning
 * @param beta Beta value for pruning
 * @param is_maximizing True if maximizing player's turn
 * @param ai_symbol AI's symbol
 * @param opponent_symbol Opponent's symbol
 * @return Best evaluation score
 */
int minimax_algorithm(FiveByFive_TTT_Board* board, int depth, int alpha, int beta,
    bool is_maximizing, char ai_symbol, char opponent_symbol);

/**
 * @brief Get best move using Minimax algorithm
 * @param board Current board state
 * @param ai_symbol AI's symbol
 * @param max_depth Maximum search depth
 * @return Pair of (row, column) for best move
 */
pair<int, int> get_best_ai_move(FiveByFive_TTT_Board* board, char ai_symbol, int max_depth = 3);

/**
 * @class FiveByFive_TTT_UI
 * @brief User Interface for 5x5 Tic-Tac-Toe
 */
class FiveByFive_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor with welcome message
     */
    FiveByFive_TTT_UI();

    /**
     * @brief Set up two players for the game
     * @return Array of two Player pointers
     */
    virtual Player<char>** setup_players() override;

    /**
     * @brief Create a player of specified type
     * @param name Player's name
     * @param symbol Player's symbol
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making move
     * @return Pointer to Move object
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Run game with custom logic for 5x5 TTT
     * @param board The game board
     * @param players Array of two players
     */
    void run_game_with_custom_loop(FiveByFive_TTT_Board* board, Player<char>* players[2]);
};

#endif // FIVE_BY_FIVE_TTT_CLASSES_H