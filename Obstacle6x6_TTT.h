#pragma once
#ifndef _OBSTACLE6X6_TTT_H
#define _OBSTACLE6X6_TTT_H

#include <iostream>
#include <vector>
#include <string>
#include "BoardGame_Classes.h"

using namespace std;

class Obstacle6x6_TTT_Board : public Board<char> {
    int round_counter;   // ??? ?? Round ???? ?????
public:
    Obstacle6x6_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    void add_obstacles();           // ????? ??????
    bool check_four_in_row(char s); // 4-in-a-row logic
};

class Obstacle6x6_TTT_UI : public UI<char> {
public:
    Obstacle6x6_TTT_UI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
