#ifndef ULTIMATE_TTT_CLASSES_H
#define ULTIMATE_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class Ultimate_TTT_Board
 * @brief Represents the Ultimate Tic Tac Toe board.
 *
 * A meta-game consisting of a 3x3 main grid where each cell contains
 * a smaller 3x3 Tic-Tac-Toe board.
 */
class Ultimate_TTT_Board : public Board<char> {
private:
    char blank_symbol = '.';

    // 9 sub-boards (3x3 each), stored as [main_row][main_col][sub_row][sub_col]
    vector<vector<vector<vector<char>>>> sub_boards;

    // Main board (3x3) - tracks which sub-boards are won
    // '.' = not won, 'X' = won by X, 'O' = won by O
    vector<vector<char>> main_board;

    // Current active sub-board (where the next move must be played)
    // -1 means player can choose any sub-board (first move or sub-board already won)
    int active_main_row;
    int active_main_col;

    // Track number of moves in each sub-board
    vector<vector<int>> sub_board_moves;

    char check_sub_board_win(int main_r, int main_c);
    bool is_sub_board_full(int main_r, int main_c);

public:
    Ultimate_TTT_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; }

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);

    pair<int, int> get_active_sub_board();

    vector<vector<char>> get_main_board() const { return main_board; }

    vector<vector<char>> get_sub_board(int main_r, int main_c) const;

    bool is_sub_board_available(int main_r, int main_c);

    tuple<int, int, int, int> convert_coordinates(int global_x, int global_y);
};

/**
 * @class Ultimate_TTT_UI
 * @brief User interface for the Ultimate Tic Tac Toe game.
 */
class Ultimate_TTT_UI : public UI<char> {
private:
    Ultimate_TTT_Board* ultimate_board_ptr;

public:
    Ultimate_TTT_UI();
    ~Ultimate_TTT_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);

    void display_board_matrix(const vector<vector<char>>& matrix) const override;

    void display_ultimate_board(Ultimate_TTT_Board* board);

    void set_board_ptr(Ultimate_TTT_Board* board);
};

#endif // ULTIMATE_TTT_CLASSES_H
