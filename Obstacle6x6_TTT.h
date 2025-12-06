/**
 * @file Obstacle6x6_TTT.h
 * @brief 6x6 Tic-Tac-Toe with dynamic obstacles variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief 6x6 Tic-Tac-Toe with Obstacles: Larger board with randomly appearing blocking obstacles.
 *
 * @game
 * - Board: 6x6 grid with dynamically placed obstacle cells
 * - Players: 2
 * - Symbols: 'X' and 'O'
 * - Obstacles: '#' symbols that block cell placement
 * - Objective: Get four in a row (horizontal, vertical, or diagonal)
 * - Challenge: Navigate around obstacles that appear every round
 *
 * @variant
 * - Larger 6x6 board requiring four in a row
 * - Dynamic obstacles appear after every 2 moves (1 complete round)
 * - 2 random obstacles are added each round
 * - Requires strategic navigation around blocked cells
 * - Increased complexity and unpredictability
 */

#pragma once
#ifndef _OBSTACLE6X6_TTT_H
#define _OBSTACLE6X6_TTT_H

#include <iostream>
#include <vector>
#include <string>
#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class Obstacle6x6_TTT_Board
 * @brief Board class for 6x6 Tic-Tac-Toe with dynamically placed obstacles
 *
 * This variant features a 6x6 grid where obstacles ('#') are randomly added
 * to the board after each round (every 2 moves). Players must navigate around
 * these obstacles while trying to achieve four symbols in a row.
 */
class Obstacle6x6_TTT_Board : public Board<char> {
    int round_counter;   ///< Round counter for tracking when to add obstacles

public:
    /**
     * @brief Constructor for 6x6 Tic-Tac-Toe with obstacles board
     *
     * Initializes a 6x6 empty grid and seeds random number generator
     * for obstacle placement.
     */
    Obstacle6x6_TTT_Board();

    /**
     * @brief Update board with player's move and add obstacles if needed
     * @param move Pointer to Move object containing coordinates and symbol
     * @return true if move is valid and applied, false otherwise
     *
     * Places the player's symbol at the specified position if valid.
     * After every 2 moves (1 complete round), adds 2 random obstacles to the board.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won by achieving four in a row
     * @param player Pointer to player to check
     * @return true if player has four in a row, false otherwise
     *
     * Checks all possible horizontal, vertical, and diagonal four-in-a-row combinations.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return false - not used in this game variant
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to player to check
     * @return true if board is full (36 moves) with no winner, false otherwise
     *
     * A draw occurs when all 36 cells are filled and no player has four in a row.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to player to check
     * @return true if game is won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

private:
    /**
     * @brief Add 2 random obstacles to empty cells on the board
     *
     * Randomly selects 2 empty cells and places obstacle symbols ('#').
     * Called automatically after each round (every 2 moves).
     */
    void add_obstacles();

    /**
     * @brief Check if a symbol has four consecutive occurrences in any direction
     * @param s Symbol to check ('X' or 'O')
     * @return true if symbol has four in a row, false otherwise
     *
     * Checks all possible lines: horizontal, vertical, and both diagonals.
     */
    bool check_four_in_row(char s);
};

/**
 * @class Obstacle6x6_TTT_UI
 * @brief User Interface for 6x6 Tic-Tac-Toe with obstacles
 *
 * Handles player input, displays the board, and manages both human
 * and computer player interactions. Computer players make random valid moves.
 */
class Obstacle6x6_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for 6x6 Tic-Tac-Toe with obstacles UI
     *
     * Initializes the UI for a 6x6 board game.
     */
    Obstacle6x6_TTT_UI();

    /**
     * @brief Get a move from a player (human or computer)
     * @param player Pointer to player making the move
     * @return Pointer to Move object containing coordinates and symbol
     *
     * For human players: prompts for row and column input (0-5)
     * For computer players: generates random valid move automatically
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif