
#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H
#include "BoardGame_Classes.h"
using namespace std;


class Four_in_a_row_board: public Board<char> {
private:
    char blank_symbol = '.';

  public:
    Four_in_a_row_board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};
class Four_in_a_row_Ui: public UI<char> {
public:
    Four_in_a_row_Ui();
    ~Four_in_a_row_Ui();
    Player<char>* create_player(string &name, char symbol);
    Move<char>* get_move(Player<char>* player) override;
};



#endif //FOUR_IN_A_ROW_H
