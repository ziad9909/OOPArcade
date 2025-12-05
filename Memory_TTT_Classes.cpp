#include "Memory_TTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Memory_TTT_Board::Memory_TTT_Board()
    : Board<char>(3, 3)
{
    srand((unsigned int)time(nullptr));

    realBoard = vector<vector<char>>(3, vector<char>(3, ' '));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = ' ';

    n_moves = 0;
}

bool Memory_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (realBoard[x][y] != ' ')
        return false;

    realBoard[x][y] = sym;
    board[x][y] = '*';

    n_moves++;
    return true;
}

bool Memory_TTT_Board::check_win(char sym) {
    // rows
    for (int i = 0; i < 3; i++) {
        if (realBoard[i][0] == sym &&
            realBoard[i][1] == sym &&
            realBoard[i][2] == sym)
            return true;
    }
    // cols
    for (int j = 0; j < 3; j++) {
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
    char s = player->get_symbol();
    char opp = (s == 'X' ? 'O' : 'X');
    return check_win(opp);
}

bool Memory_TTT_Board::is_draw(Player<char>* player) {
    return n_moves == 9 &&
        !is_win(player) &&
        !is_lose(player);
}

bool Memory_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

// ======================
// UI
// ======================
Move<char>* Memory_TTT_UI::get_move(Player<char>* player)
{
    Board<char>* board = player->get_board_ptr();

    if (player->get_type() == PlayerType::COMPUTER)
    {
        int x, y;
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_cell(x, y) != ' ');

        char sym = player->get_symbol();
        cout << "Computer chooses: (" << x << ", " << y << ")\n";
        return new Move<char>(x, y, sym);
    }

    int x, y;
    cout << player->get_name()
        << " enter row and column: ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}
