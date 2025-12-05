/**
 * @file Word_TTT.h
 * @brief Word Tic-Tac-Toe variant implementation
 * @author Your Name/Team
 * @date 2024
 * @version 1.0
 * @copyright Copyright (c) 2024 Board Game Collection
 *
 * @brief Word Tic-Tac-Toe: Players create words instead of X's and O's.
 *
 * @game
 * - Board: 3x3 grid
 * - Players: 2
 * - Objective: Create a valid 3-letter word in any row, column, or diagonal
 * - Words must be from a predefined dictionary
 *
 * @variant
 * - Players can use letters to form words
 * - Words must be valid English words
 * - Dictionary-based validation
 * - Strategic letter placement to block opponent's words
 */

#pragma once
#ifndef _WORD_TTT_H
#define _WORD_TTT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class Word_TTT_Board
 * @brief Board class for Word Tic-Tac-Toe
 *
 * Implements a 3x3 grid where players place letters to form valid words.
 * Words are validated against a dictionary of approved words.
 */
class Word_TTT_Board : public Board<char> {
    unordered_set<string> dictionary; ///< Dictionary of valid 3-letter words
    int last_x;                       ///< X coordinate of last move
    int last_y;                       ///< Y coordinate of last move

public:
    /**
     * @brief Constructor for Word Tic-Tac-Toe board
     *
     * Initializes 3x3 board and loads default dictionary.
     */
    Word_TTT_Board();

    /**
     * @brief Update board with player's move
     * @param move Pointer to Move object containing position and letter
     * @return true if move is valid and applied, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to player to check
     * @return true if player has formed a valid word, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to player to check
     * @return false - players cannot lose directly
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to current player
     * @return true if board is full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to current player
     * @return true if game is won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

private:
    /**
     * @brief Load dictionary from file
     * @param filename Path to dictionary file
     */
    void load_dictionary(const string& filename);

    /**
     * @brief Check if last move created a winning word
     * @return true if a valid word was formed, false otherwise
     */
    bool check_win();
};

/**
 * @class Word_TTT_UI
 * @brief User Interface for Word Tic-Tac-Toe
 *
 * Handles player input/output for Word Tic-Tac-Toe game.
 */
class Word_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Word Tic-Tac-Toe UI
     */
    Word_TTT_UI();

    /**
     * @brief Get a move from a player
     * @param player Pointer to player making the move
     * @return Pointer to Move object containing player's move
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Create a player object
     * @param name Player's name
     * @param symbol Player's symbol (letter character)
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif