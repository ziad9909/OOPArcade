/**
 * @file Timed_TTT_Classes.h
 * @brief Timed Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Timed Tic-Tac-Toe: Oldest moves disappear after every 3 moves.
 *
 * @game
 * - Board: 3x3 grid
 * - Players: 2
 * - Objective: Get three in a row
 * - Special rule: After every 3 moves, the oldest move disappears
 * - Dynamic board that changes throughout the game
 *
 * @variant
 * - Time-based element with disappearing moves
 * - Strategy must account for moves being removed
 * - Encourages aggressive play before moves disappear
 */

#pragma once
#ifndef TIMED_TTT_CLASSES_H
#define TIMED_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <queue>

using namespace std;

/**
 * @class Timed_TTT_Board
 * @brief A Tic-Tac-Toe variant where oldest moves disappear after every 3 moves.
 */
class Timed_TTT_Board : public Board<char> {
private:
    queue<pair<int, int>> moveHistory; ///< Tracks the order of moves
    char emptyCell = '.';              ///< Character representing empty cell

    /**
     * @brief Remove the oldest move from the board after every 3 moves.
     */
    void removeOldestMove();

    /**
     * @brief Check if a player has three in a row.
     * @param symbol Player's symbol to check
     * @return true if player has three in a row, false otherwise
     */
    bool checkThreeInRow(char symbol);

public:
    /**
     * @brief Constructor for Timed Tic-Tac-Toe board
     */
    Timed_TTT_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object
     * @return true if move is valid and applied, false otherwise
     */
    virtual bool update_board(Move<char>* move) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to player to check
     * @return true if game has reached maximum moves without winner
     */
    virtual bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to player to check
     * @return true if player has three in a row, false otherwise
     */
    virtual bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return false - not used in this game
     */
    virtual bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if game is won or drawn, false otherwise
     */
    virtual bool game_is_over(Player<char>* player) override;
};

/**
 * @class Timed_TTT_UI
 * @brief User Interface for Timed Tic-Tac-Toe game.
 */
class Timed_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Timed Tic-Tac-Toe UI
     */
    Timed_TTT_UI();

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
};

#endif // TIMED_TTT_CLASSES_H