#include "FiveByFiveTTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// --- Board Implementation ---

FiveByFive_TTT_Board::FiveByFive_TTT_Board() : Board(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool FiveByFive_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != blank_symbol)
        return false;

    board[x][y] = mark;
    n_moves++;
    return true;
}

// Check for 3-in-a-row sequences for a player
bool FiveByFive_TTT_Board::check_win(char sym) {
    int count = 0;

    // Rows
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j <= 2; ++j)
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                count++;

    // Columns
    for (int j = 0; j < 5; ++j)
        for (int i = 0; i <= 2; ++i)
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                count++;

    // Diagonals (down-right)
    for (int i = 0; i <= 2; ++i)
        for (int j = 0; j <= 2; ++j)
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                count++;

    // Diagonals (down-left)
    for (int i = 0; i <= 2; ++i)
        for (int j = 2; j < 5; ++j)
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym)
                count++;

    return count > 0; // True if at least one sequence exists
}

bool FiveByFive_TTT_Board::is_win(Player<char>* player) {
    return check_win(player->get_symbol());
}

bool FiveByFive_TTT_Board::is_draw(Player<char>* player) {
    return n_moves >= 24 && !is_win(player); // 24 moves = all except last empty cell
}

bool FiveByFive_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// --- UI Implementation ---

FiveByFive_TTT_UI::FiveByFive_TTT_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe!", 3) {}

Player<char>* FiveByFive_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer") << " player: "
        << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* FiveByFive_TTT_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << ", enter your move (row and col 0-4): ";
        cin >> x >> y;
    }
    else { // COMPUTER
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (player->get_board_ptr()->get_cell(x, y) != '.');
        cout << "Computer chose (" << x << "," << y << ")\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}
