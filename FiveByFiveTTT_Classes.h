#pragma once
#ifndef FIVE_BY_FIVE_TTT_CLASSES_H
#define FIVE_BY_FIVE_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>

using namespace std;

/**
 * @class FiveByFive_TTT_Board
 * @brief Represents a 5x5 Tic-Tac-Toe board where players compete to create the most three-in-a-row sequences.
 */
class FiveByFive_TTT_Board : public Board<char> {
private:
    /**
     * @brief Counts all three-in-a-row sequences for a given symbol.
     * @param symbol The symbol (X or O) to check.
     * @return The total number of three-in-a-row sequences for the symbol.
     */
    int count_sequences(char symbol);

public:
    /**
     * @brief Constructs a 5x5 Tic-Tac-Toe board.
     */
    FiveByFive_TTT_Board();

    // --- Virtual functions implementation ---

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object.
     * @return true if the move is valid, false otherwise.
     */
    virtual bool update_board(Move<char>* move);

    /**
     * @brief Checks if the game ended in a draw.
     * @param player Current player (not used for draw check).
     * @return true if the board is full, false otherwise.
     */
    virtual bool is_draw(Player<char>* player);

    /**
     * @brief Checks if a player has won (has more sequences than opponent).
     * @param player Current player to check.
     * @return true if current player has more three-in-a-row sequences.
     */
    virtual bool is_win(Player<char>* player);

    /**
     * @brief Checks if a player has lost (opponent has more sequences).
     * @param player Current player to check.
     * @return true if opponent has more three-in-a-row sequences.
     */
    virtual bool is_lose(Player<char>* player);

    /**
     * @brief Checks if the game is over.
     * @param player Current player.
     * @return true if the board is full (after 24 moves).
     */
    virtual bool game_is_over(Player<char>* player);

    /**
     * @brief Gets the count of sequences for both players.
     * @return Pair of integers (X sequences, O sequences).
     */
    pair<int, int> get_sequence_counts();

    /**
     * @brief Gets the number of moves made (public accessor for n_moves).
     */
    int get_move_count() const { return n_moves; }
};

/**
 * @class FiveByFive_TTT_UI
 * @brief User Interface for the 5x5 Tic-Tac-Toe game.
 */
class FiveByFive_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructs the UI with welcome message.
     */
    FiveByFive_TTT_UI();

    /**
     * @brief Sets up two players for the game.
     * @return Array of two Player pointers.
     */
    virtual Player<char>** setup_players();

    /**
     * @brief Creates a player of specified type.
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets a move from a player.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Runs the game with custom logic for 5x5 TTT.
     * @param board The game board.
     * @param players Array of two players.
     */
    void run_game_with_custom_loop(FiveByFive_TTT_Board* board, Player<char>* players[2]);
};

#endif // FIVE_BY_FIVE_TTT_CLASSES_H