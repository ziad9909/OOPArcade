// Memory_TTT_Classes.cpp
#include "Memory_TTT_Classes.h"
#include <iostream>

Memory_TTT_Board::Memory_TTT_Board()
    : Board<char>(3, 3) 
{
    // initial visible board: all spaces (user sees empty)
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = ' ';

    // initial real board: all spaces (no X or O yet)
    realBoard = vector<vector<char>>(3, vector<char>(3, ' '));

    n_moves = 0;
}


bool Memory_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    // bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;

    
    if (realBoard[x][y] != ' ') return false;

    
    realBoard[x][y] = sym;
    board[x][y] = '*';

    ++n_moves;
    return true;
}


bool Memory_TTT_Board::check_win(char sym) {
    // rows
    for (int i = 0; i < 3; ++i) {
        if (realBoard[i][0] == sym &&
            realBoard[i][1] == sym &&
            realBoard[i][2] == sym)
            return true;
    }

    // cols
    for (int j = 0; j < 3; ++j) {
        if (realBoard[0][j] == sym &&
            realBoard[1][j] == sym &&
            realBoard[2][j] == sym)
            return true;
    }

    // diagonals
    if (realBoard[0][0] == sym &&
        realBoard[1][1] == sym &&
        realBoard[2][2] == sym)
        return true;

    if (realBoard[0][2] == sym &&
        realBoard[1][1] == sym &&
        realBoard[2][0] == sym)
        return true;

    return false;
}

bool Memory_TTT_Board::is_win(Player<char>* player) {
    return check_win(player->get_symbol());
}

bool Memory_TTT_Board::is_lose(Player<char>* player) {
    char my = player->get_symbol();
    char opp = (my == 'X') ? 'O' : 'X';
    return check_win(opp);
}

bool Memory_TTT_Board::is_draw(Player<char>* player) {
    
    if (n_moves >= rows * columns && !is_win(player) && !is_lose(player))
        return true;
    return false;
}

bool Memory_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

// -------------------
// UI implementation
// -------------------
Move<char>* Memory_TTT_UI::get_move(Player<char>* player) {
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column (e.g. 0 1): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}