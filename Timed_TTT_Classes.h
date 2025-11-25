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
     * @brief Removes the oldest move from the board after every 3 moves.
     */
    void removeOldestMove();

    /**
     * @brief Checks if a player has three in a row.
     */
    bool checkThreeInRow(char symbol);

public:
    // Constructor
    Timed_TTT_Board();

    // Virtual function implementations
    virtual bool update_board(Move<char>* move);
    virtual bool is_draw(Player<char>* player);
    virtual bool is_win(Player<char>* player);
    virtual bool is_lose(Player<char>* player) { return false; }
    virtual bool game_is_over(Player<char>* player);
};

//-----------------------------------------------------

/**
 * @class Timed_TTT_UI
 * @brief User Interface for Timed Tic-Tac-Toe game.
 */
class Timed_TTT_UI : public UI<char> {
public:
    /**
     * @brief Constructs a Timed_TTT_UI object.
     */
    Timed_TTT_UI();

    /**
     * @brief Sets up players for the game.
     */
    virtual Player<char>** setup_players();

    /**
     * @brief Creates a player of the specified type.
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // TIMED_TTT_CLASSES_H