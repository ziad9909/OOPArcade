/**
 * @file 4x4_TTT_Classes.h
 * @brief 4x4 Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief 4x4 Tic-Tac-Toe: Larger board requiring four in a row to win.
 *
 * @game
 * - Board: 4x4 grid
 * - Players: 2
 * - Symbols: 'X' and 'O'
 * - Objective: Get four in a row (horizontal, vertical, or diagonal)
 * - More spaces mean longer games and more strategic possibilities
 *
 * @variant
 * - Larger board than classic 3x3
 * - Requires four in a row instead of three
 * - More potential winning combinations
 * - Reduced chance of early draws
 */

#ifndef FOUR_BY_FOUR_TTT_CLASSES_H
#define FOUR_BY_FOUR_TTT_CLASSES_H

#include "BoardGame_Classes.h"

 /**
  * @class FourByFour_TTT_Board
  * @brief Board class for 4x4 Tic-Tac-Toe
  */
class FourByFour_TTT_Board : public Board<char> {
private:
    char blank = '.'; ///< Symbol representing empty cell

public:
    /**
     * @brief Constructor for 4x4 Tic-Tac-Toe board
     */
    FourByFour_TTT_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object
     * @return true if move is valid and applied, false otherwise
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
    bool is_lose(Player<char>* player) override { return false; }

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

    /**
     * @brief Validate if move is valid
     * @param fromX Source X coordinate
     * @param fromY Source Y coordinate
     * @param toX Destination X coordinate
     * @param toY Destination Y coordinate
     * @param symbol Player's symbol
     * @return true if move is valid, false otherwise
     */
    bool valid_move(int fromX, int fromY, int toX, int toY, char symbol);
};

/**
 * @class FourByFour_TTT_UI
 * @brief User Interface for 4x4 Tic-Tac-Toe
 */
class FourByFour_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for 4x4 Tic-Tac-Toe UI
     */
    FourByFour_TTT_UI();

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