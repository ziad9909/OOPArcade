#pragma once
#ifndef _WORD_TTT_H
#define _WORD_TTT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "BoardGame_Classes.h"

using namespace std;

class Word_TTT_Board : public Board<char> {
    unordered_set<string> dictionary;
    int last_x, last_y;

public:
    Word_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    void load_dictionary(const string& filename);
    bool check_win();

};

class Word_TTT_UI : public UI<char> {
public:
    Word_TTT_UI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif