#ifndef MISERE_TTT_CLASSES_H
#define MISERE_TTT_CLASSES_H

#include "BoardGame_Classes.h"

class Misere_TTT_Board : public Board<char> {
public:
    Misere_TTT_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    // New methods for AI (minimax)
    Move<char>* get_best_move_for_ai(char aiSymbol, char humanSymbol);

	//Helpers for minimax
private:
    bool check_three(char sym); 
    int evaluate_state(char aiSym, char huSym, int depth);
    int minimax(bool isMaximizing, char aiSym, char huSym, int depth, int alpha, int beta);

};

class Misere_TTT_UI : public UI<char> {
public:
    Misere_TTT_UI();
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif 