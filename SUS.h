#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
using namespace std;

class SUS_board : public Board<char> {
public:
 SUS_board();
 bool update_board(Move<char>* move);
 bool is_win(Player<char>* player);
 bool is_lose(Player<char>* player);
 bool is_draw(Player<char>* player);
 bool game_is_over(Player<char>* player);
 int get_score(Player<char>* player);

private:
 char blank_symbol = '.';
};

class SUS_player : public UI<char> {
public:
 SUS_player();
 ~SUS_player();
 Player<char>* create_player(string& name, char symbol, PlayerType type) override;
 Player<char>** setup_players() override;
 Move<char>* get_move(Player<char>* player) override;
};

#endif