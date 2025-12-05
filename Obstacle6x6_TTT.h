/**
 * @file Obstacle6x6_TTT.h
 * @brief 6x6 Tic-Tac-Toe with obstacles variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief 6x6 Tic-Tac-Toe with Obstacles: Larger board with blocking obstacles.
 *
 * @game
 * - Board: 6x6 grid with obstacle cells
 * - Players: 2
 * - Symbols: 'X' and 'O'
 * - Objective: Get four in a row (horizontal, vertical, or diagonal)
 * - Obstacles: Certain cells cannot be played
 * - Obstacles may change/rotate during game
 *
 * @variant
 * - Larger 6x6 board
 * - Obstacle cells block moves
 * - Dynamic obstacles that may change
 * - Requires navigation around blocked cells
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
 * @brief Board class for 6x6 Tic-Tac-Toe with obstacles
 */
class Obstacle6x6_TTT_Board : public Board<char> {
    int round_counter;   ///< Round counter for obstacle rotation

public:
    /**
     * @brief Constructor for 6x6 Tic-Tac-Toe with obstacles board
     */
    Obstacle6x6_TTT_Board();

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
     * @return true if opponent has four in a row, false otherwise
     */
    bool is_lose(Player<char>* player) override;

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

private:
    /**
     * @brief Add obstacles to board
     */
    void add_obstacles();

    /**
     * @brief Check for four in a row
     * @param s Symbol to check
     * @return true if symbol has four in a row, false otherwise
     */
    bool check_four_in_row(char s);
};

/**
 * @class Obstacle6x6_TTT_UI
 * @brief User Interface for 6x6 Tic-Tac-Toe with obstacles
 */
class Obstacle6x6_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for 6x6 Tic-Tac-Toe with obstacles UI
     */
    Obstacle6x6_TTT_UI();

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif