/**
 * @file 4x4_TTT_Classes.h
 * @brief 4x4 Moving Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief 4x4 Moving Tic-Tac-Toe: Players move existing pieces instead of placing new ones.
 *
 * @game
 * - Board: 4x4 grid with pre-placed tokens
 * - Players: 2
 * - Symbols: 'X' and 'O'
 * - Objective: Get three in a row (horizontal, vertical, or diagonal)
 * - Movement: Players move their existing tokens one step at a time
 * - Starting Setup: Each player has 4 tokens placed on opposite sides
 *
 * @variant
 * - Tokens are moved rather than placed
 * - No new pieces are added during play
 * - Strategic positioning and blocking
 * - Game continues until someone wins (no draws)
 */

#ifndef FOUR_BY_FOUR_TTT_CLASSES_H
#define FOUR_BY_FOUR_TTT_CLASSES_H

#include "BoardGame_Classes.h"

 /**
  * @class FourByFour_TTT_Board
  * @brief Board class for 4x4 Moving Tic-Tac-Toe where players move existing tokens
  *
  * This board variant features a 4x4 grid where players start with 4 pre-placed tokens each.
  * Instead of placing new tokens, players move their existing tokens one step horizontally
  * or vertically. The objective is to align three tokens in a row.
  */
class FourByFour_TTT_Board : public Board<char> {
private:
    char blank = '.'; ///< Symbol representing empty cell

public:
    /**
     * @brief Constructor for 4x4 Moving Tic-Tac-Toe board
     *
     * Initializes a 4x4 grid with pre-placed tokens:
     * - X tokens at positions (0,1), (0,3), (3,0), (3,2)
     * - O tokens at positions (0,0), (0,2), (3,1), (3,3)
     */
    FourByFour_TTT_Board();

    /**
     * @brief Update board by moving a token from source to destination
     * @param move Pointer to Move object containing destination coordinates
     * @return true if move is valid and applied, false otherwise
     *
     * Prompts user for source position and validates the move before applying.
     * Move must be one step horizontally or vertically to an empty cell.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won by getting three in a row
     * @param player Pointer to player to check
     * @return true if player has three in a row, false otherwise
     *
     * Checks all possible horizontal, vertical, and diagonal combinations.
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
     * @return false - this variant has no draw condition
     *
     * The game continues indefinitely until one player wins.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if any player has won, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Validate if a token movement is legal
     * @param fromX Source row coordinate (0-3)
     * @param fromY Source column coordinate (0-3)
     * @param toX Destination row coordinate (0-3)
     * @param toY Destination column coordinate (0-3)
     * @param symbol Player's symbol ('X' or 'O')
     * @return true if move is valid, false otherwise
     *
     * A valid move requires:
     * - Source cell contains the player's symbol
     * - Destination cell is empty
     * - Movement is exactly one step horizontally or vertically
     */
    bool valid_move(int fromX, int fromY, int toX, int toY, char symbol);
};

/**
 * @class FourByFour_TTT_UI
 * @brief User Interface for 4x4 Moving Tic-Tac-Toe game
 *
 * Handles player input for source and destination positions and
 * manages the game display and player creation.
 */
class FourByFour_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for 4x4 Moving Tic-Tac-Toe UI
     *
     * Initializes the UI with welcome message and win condition of 3 in a row.
     */
    FourByFour_TTT_UI();

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
     * @return Pointer to Move object containing destination coordinates
     *
     * Prompts the player to enter destination cell coordinates.
     * Source coordinates are requested in update_board().
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif