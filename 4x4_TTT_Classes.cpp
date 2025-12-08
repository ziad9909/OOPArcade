﻿#include "4x4_TTT_Classes.h"
#include <iostream>
using namespace std;

FourByFour_TTT_Board::FourByFour_TTT_Board() : Board(4, 4)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank;

    // starting positions:
    // X at row 0 and row 3
    board[0][1] = 'X';
    board[0][3] = 'X';
    board[3][0] = 'X';
    board[3][2] = 'X';

    // O at row 0 and row 3
    board[0][0] = 'O';
    board[0][2] = 'O';
    board[3][1] = 'O';
    board[3][3] = 'O';
}

bool FourByFour_TTT_Board::valid_move(int x1, int y1, int x2, int y2, char sym)
{
    if (x1 < 0 || x1 >= 4 || y1 < 0 || y1 >= 4) return false;
    if (x2 < 0 || x2 >= 4 || y2 < 0 || y2 >= 4) return false;

    if (board[x1][y1] != sym) return false;
    if (board[x2][y2] != blank) return false;

    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    // move must be 1 step horizontally or vertically ONLY
    return (dx + dy == 1);
}

bool FourByFour_TTT_Board::update_board(Move<char>* move)
{
    char sym = move->get_symbol();

    int x2 = move->get_x();
    int y2 = move->get_y();

    // ask user for source cell
    cout << "Enter source position of your token (row col): ";
    int x1, y1;
    cin >> x1 >> y1;

    if (!valid_move(x1, y1, x2, y2, sym))
        return false;

    board[x1][y1] = blank;
    board[x2][y2] = sym;
    return true;
}

bool FourByFour_TTT_Board::is_win(Player<char>* player)
{
    char s = player->get_symbol();

    // check rows
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 2; j++)
            if (board[i][j] == s && board[i][j + 1] == s && board[i][j + 2] == s)
                return true;

    // check cols
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 2; i++)
            if (board[i][j] == s && board[i + 1][j] == s && board[i + 2][j] == s)
                return true;

    // diag 1
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (board[i][j] == s && board[i + 1][j + 1] == s && board[i + 2][j + 2] == s)
                return true;

    // diag 2
    for (int i = 0; i < 2; i++)
        for (int j = 2; j < 4; j++)
            if (board[i][j] == s && board[i + 1][j - 1] == s && board[i + 2][j - 2] == s)
                return true;

    return false;
}

bool FourByFour_TTT_Board::is_draw(Player<char>* player)
{
    return false; // no draw — endless until someone wins
}

bool FourByFour_TTT_Board::game_is_over(Player<char>* player)
{
    return is_win(player);
}

/* UI */

FourByFour_TTT_UI::FourByFour_TTT_UI()
    : UI<char>("Welcome to 4x4 Moving Tic-Tac-Toe!", 3)
{
}

Player<char>* FourByFour_TTT_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

Move<char>* FourByFour_TTT_UI::get_move(Player<char>* p)
{
    int x, y;
    cout << p->get_name() << " enter destination cell (row col): ";
    cin >> x >> y;

    return new Move<char>(x, y, p->get_symbol());

}