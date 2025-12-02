#include "Four_in_a_row.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

Four_in_a_row_board::Four_in_a_row_board() : Board<char>(6,7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Four_in_a_row_board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    if (col < 0 || col >= columns) return false;

    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == blank_symbol) {
            board[row][col] = toupper(mark);
            n_moves++;
            return true;
        }
    }
    return false;
}

bool Four_in_a_row_board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    for (int r = 0; r < rows; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym && board[r][c+3] == sym) return true;
    for (int c = 0; c < columns; c++)
        for (int r = 0; r <= rows - 4; r++)
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym && board[r+3][c] == sym) return true;
    for (int r = 0; r <= rows - 4; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym && board[r+3][c+3] == sym) return true;
    for (int r = 3; r < rows; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == sym && board[r-1][c+1] == sym && board[r-2][c+2] == sym && board[r-3][c+3] == sym) return true;
    return false;
}

bool Four_in_a_row_board::is_draw(Player<char>* player) {
    for (int c = 0; c < columns; c++)
        if (board[0][c] == blank_symbol) return false;
    return true;
}

bool Four_in_a_row_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Four_in_a_row_Ui::Four_in_a_row_Ui() : UI<char>("Welcome to Four-in-a-Row", 3) {}

Four_in_a_row_Ui::~Four_in_a_row_Ui() {}

Player<char>* Four_in_a_row_Ui::create_player(string &name, char symbol) {
    PlayerType type = PlayerType::HUMAN;  // أو COMPUTE لو حابب
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Four_in_a_row_Ui::get_move(Player<char>* player) {
    int col;
    if (player->get_type() == PlayerType::COMPUTER) {
        do {
            col = rand() % 7;
        } while (player->get_board_ptr()->get_cell(0, col) != '.');
        cout << player->get_name() << " chooses column " << col << endl;
    } else {
        do {
            cout << player->get_name() << ", enter column (0-6): ";
            cin >> col;
        } while (col < 0 || col > 6 || player->get_board_ptr()->get_cell(0, col) != '.');
    }
    return new Move<char>(0, col, player->get_symbol());
}
