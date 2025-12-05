#ifndef PYRAMID_TTT_CLASSES_H
#define PYRAMID_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;


class Pyramid_TTT_Board : public Board<char> {
public:
    Pyramid_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Pyramid_TTT_UI : public UI<char> {
public:
    Pyramid_TTT_UI() : UI<char>(3) {}

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

class RandomComputerPlayer : public Player<char> {
public:
    RandomComputerPlayer(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER) {}

    Move<char>* get_computer_move() {
        Board<char>* board = this->get_board_ptr();

        while (true) {
            int x = rand() % board->get_rows();
            int y = rand() % board->get_columns();

            if (board->get_cell(x, y) == '_') {
                return new Move<char>(x, y, this->symbol);
            }
        }
    }
};
#endif