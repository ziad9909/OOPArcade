/**
 * @file XO_Classes.h
 * @brief Classic Tic-Tac-Toe (X-O) implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Classic Tic-Tac-Toe: The traditional X and O game.
 *
 * @game
 * - Board: 3x3 grid
 * - Players: 2
 * - Symbols: Player 1 uses 'X', Player 2 uses 'O'
 * - Objective: Get three of your symbols in a row (horizontal, vertical, or diagonal)
 * - Turns alternate starting with Player 1
 *
 * @variant
 * - Standard rules with no variations
 * - Base implementation for all other variants
 * - Simple and well-known gameplay
 */

#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class X_O_Board
 * @brief Board class for classic Tic-Tac-Toe (X-O)
 *
 * Implements the traditional 3x3 Tic-Tac-Toe game.
 */
class X_O_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol representing empty cell

public:
    /**
     * @brief Constructor for classic Tic-Tac-Toe board
     */
    X_O_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object
     * @return true if move is valid and applied, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to player to check
     * @return true if player has three in a row, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return false - not used in classic game
     */
    bool is_lose(Player<char>* player) override { return false; };

    /**
     * @brief Check if game is a draw
     * @param player Pointer to player to check
     * @return true if board is full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if game is won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class XO_UI
 * @brief User Interface for classic Tic-Tac-Toe
 */
class XO_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Tic-Tac-Toe UI
     */
    XO_UI();

    /**
     * @brief Destructor
     */
    ~XO_UI() {};

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object
     */
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // XO_CLASSES_H