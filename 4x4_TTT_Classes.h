#ifndef FOUR_BY_FOUR_TTT_CLASSES_H
#define FOUR_BY_FOUR_TTT_CLASSES_H

#include "BoardGame_Classes.h"

class FourByFour_TTT_Board : public Board<char> {
private:
    char blank = '.';

public:
    FourByFour_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool valid_move(int fromX, int fromY, int toX, int toY, char symbol);
};



class FourByFour_TTT_UI : public UI<char> {
public:
    FourByFour_TTT_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};


#endif