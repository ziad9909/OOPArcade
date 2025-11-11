#pragma once
#ifndef NUMERICAL_TTT_CLASSES_H
#define NUMERICAL_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <numeric> // For std::iota

using namespace std;

// This class will hold the game logic for Numerical Tic-Tac-Toe
class Numerical_TTT_Board : public Board<int> {
private:
    // Tracks which numbers are still available for each player
    vector<int> odd_nums;  // For Player 1 [cite: 344]
    vector<int> even_nums; // For Player 2 [cite: 344]

    // A helper function to check all 8 lines for a win
    bool check_win();

public:
    // Constructor
    Numerical_TTT_Board();

    // --- Must implement all virtual functions from Board<T> ---

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<int> object. The move's symbol is the number.
     * @return true if the move is valid, false otherwise.
     */
    virtual bool update_board(Move<int>* move);

    /**
     * @brief Checks if the game has ended in a draw.
     * @return true if the board is full and no one has won[cite: 346].
     */
    virtual bool is_draw(Player<int>* player);

    /**
     * @brief Checks if a winning condition (any line sums to 15) is met[cite: 346].
     */
    virtual bool is_win(Player<int>* player);

    /**
     * @brief Checks if a player has lost. (Not used in this game).
     */
    virtual bool is_lose(Player<int>* player) { return false; }

    /**
     * @brief Checks if the game is over (win or draw).
     */
    virtual bool game_is_over(Player<int>* player);

    // --- Helper functions for this specific game ---

    /**
     * @brief Gets the list of available numbers for a player.
     * @param player_symbol 1 for Odd (Player 1), 2 for Even (Player 2).
     */
    vector<int> get_available_moves(int player_symbol);
};

#endif // NUMERICAL_TTT_CLASSES_H

// ... (keep the Numerical_TTT_Board class definition above)

/**
 * @class Numerical_TTT_UI
 * @brief User Interface class for the Numerical Tic-Tac-Toe game.
 */
class Numerical_TTT_UI : public UI<int> {
public:
    /**
     * @brief Constructs a Numerical_TTT_UI object.
     */
    Numerical_TTT_UI();

    /**
     * @brief Overrides the base function to set up players.
     * THIS IS THE KEY: We assign symbol '1' to Player 1 (Odd)
     * and symbol '2' to Player 2 (Even).
     */
    virtual Player<int>** setup_players();

    /**
     * @brief Creates a player of the specified type.
     */
    virtual Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     */
    virtual Move<int>* get_move(Player<int>* player);
};