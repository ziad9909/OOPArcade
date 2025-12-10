#ifndef MEMORY_TTT_CLASSES_H
#define MEMORY_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

/**
 * @class Memory_TTT_Board
 * @brief Hidden-memory Tic-Tac-Toe board
 */
class Memory_TTT_Board : public Board<char> {
private:
    vector<vector<char>> realBoard;

public:
    Memory_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void reveal_board();
    void print() const;
private:
    bool check_win(char sym);
};

/**
 * @class Memory_TTT_UI
 * @brief UI handling for Memory Tic-Tac-Toe
 */
class Memory_TTT_UI : public UI<char> {
public:
    Memory_TTT_UI() : UI(3) {}
    Move<char>* get_move(Player<char>* player) override;
};

#endif