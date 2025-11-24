#ifndef FIVEBYFIVETTT_CLASSES_H
#define FIVEBYFIVETTT_CLASSES_H

#include "BoardGame_Classes.h"

class FiveByFive_TTT_Board : public Board<char> {
public:
    const char blank_symbol = '.';
    FiveByFive_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int count_three_in_a_row(char sym);
};

class FiveByFive_TTT_UI : public UI<char> {
public:
    FiveByFive_TTT_UI();
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FIVEBYFIVETTT_CLASSES_H
