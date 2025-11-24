#pragma once
#ifndef FIVEBYFIVE_TTT_CLASSES_H
#define FIVEBYFIVE_TTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class FiveByFive_TTT_Board : public Board<char> {
private:
    char blank_symbol = '.';

    bool check_win(char sym);

public:
    FiveByFive_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class FiveByFive_TTT_UI : public UI<char> {
public:
    FiveByFive_TTT_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FIVEBYFIVE_TTT_CLASSES_H
