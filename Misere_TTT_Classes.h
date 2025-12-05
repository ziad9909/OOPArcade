/**
 * @file Misere_TTT_Classes.h
 * @brief Misère Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Misère Tic-Tac-Toe: Players try to AVOID getting three in a row.
 *
 * @game
 * - Board: 3x3 grid
 * - Players: 2
 * - Objective: Avoid being the player who completes three in a row
 * - Standard Tic-Tac-Toe rules, but winning is losing
 *
 * @variant
 * - Also known as "Reverse Tic-Tac-Toe" or "Avoid Tic-Tac-Toe"
 * - Player who gets three in a row LOSES the game
 * - Strategic play involves forcing opponent into winning
 * - Often ends in draw as players avoid completing lines
 */

#ifndef MISERE_TTT_CLASSES_H
#define MISERE_TTT_CLASSES_H

#include "BoardGame_Classes.h"

 /**
  * @class Misere_TTT_Board
  * @brief Board class for Misère Tic-Tac-Toe
  *
  * Implements Misère Tic-Tac-Toe where getting three in a row means losing.
  */
class Misere_TTT_Board : public Board<char> {
public:
    /**
     * @brief Constructor for Misère Tic-Tac-Toe board
     */
    Misere_TTT_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object
     * @return true if move is valid and applied, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to player to check
     * @return true if player has NOT completed three in a row, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return true if player has completed three in a row (loses), false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to player to check
     * @return true if board is full with no loser, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if game has a loser or is drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Get best move for AI using minimax
     * @param aiSymbol AI player's symbol
     * @param humanSymbol Human player's symbol
     * @return Pointer to best Move object
     */
    Move<char>* get_best_move_for_ai(char aiSymbol, char humanSymbol);

private:
    /**
     * @brief Check for three in a row
     * @param sym Symbol to check
     * @return true if symbol has three in a row, false otherwise
     */
    bool check_three(char sym);

    /**
     * @brief Evaluate board state
     * @param aiSym AI player's symbol
     * @param huSym Human player's symbol
     * @param depth Current depth in search
     * @return Evaluation score
     */
    int evaluate_state(char aiSym, char huSym, int depth);

    /**
     * @brief Minimax algorithm with alpha-beta pruning
     */
    int minimax(bool isMaximizing, char aiSym, char huSym, int depth, int alpha, int beta);
};

/**
 * @class Misere_TTT_UI
 * @brief User Interface for Misère Tic-Tac-Toe
 */
class Misere_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Misère Tic-Tac-Toe UI
     */
    Misere_TTT_UI();

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif