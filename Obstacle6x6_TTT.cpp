#include "Obstacle6x6_TTT.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Obstacle6x6_TTT_Board::Obstacle6x6_TTT_Board()
    : Board<char>(6, 6), round_counter(0)
{
    srand((unsigned int)time(nullptr));

    for (auto& row : board)
        fill(row.begin(), row.end(), ' ');

    n_moves = 0;
}

bool Obstacle6x6_TTT_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= 6 || y < 0 || y >= 6 || board[x][y] != ' ')
        return false;

    board[x][y] = s;
    n_moves++;

    // ?? Round (???? 2 ??????) ??? ?????
    if (n_moves % 2 == 0)
    {
        add_obstacles();
    }

    return true;
}

void Obstacle6x6_TTT_Board::add_obstacles()
{
    int added = 0;

    while (added < 2)
    {
        int x = rand() % 6;
        int y = rand() % 6;

        if (board[x][y] == ' ')
        {
            board[x][y] = '#';  // obstacle
            added++;
        }
    }
}

bool Obstacle6x6_TTT_Board::check_four_in_row(char s)
{
    // horizontal
    for (int i = 0; i < 6; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == s && board[i][j + 1] == s &&
                board[i][j + 2] == s && board[i][j + 3] == s)
                return true;

    // vertical
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j < 6; j++)
            if (board[i][j] == s && board[i + 1][j] == s &&
                board[i + 2][j] == s && board[i + 3][j] == s)
                return true;

    // diagonal (down-right)
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == s && board[i + 1][j + 1] == s &&
                board[i + 2][j + 2] == s && board[i + 3][j + 3] == s)
                return true;

    // diagonal (up-right)
    for (int i = 3; i < 6; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == s && board[i - 1][j + 1] == s &&
                board[i - 2][j + 2] == s && board[i - 3][j + 3] == s)
                return true;

    return false;
}

bool Obstacle6x6_TTT_Board::is_win(Player<char>* player)
{
    char s = player->get_symbol();
    return check_four_in_row(s);
}

bool Obstacle6x6_TTT_Board::is_lose(Player<char>* player)
{
    return false;
}

bool Obstacle6x6_TTT_Board::is_draw(Player<char>* player)
{
    return n_moves == 36 && !is_win(player);
}

bool Obstacle6x6_TTT_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}

// ================ UI ================

Obstacle6x6_TTT_UI::Obstacle6x6_TTT_UI()
    : UI(6)
{
}

Move<char>* Obstacle6x6_TTT_UI::get_move(Player<char>* player)
{
    Board<char>* b = player->get_board_ptr();

    int x, y;

    // ============================
    //   COMPUTER PLAY RANDOM
    // ============================
    if (player->get_type() == PlayerType::COMPUTER)
    {
        do {
            x = rand() % 6;
            y = rand() % 6;
        } while (b->get_cell(x, y) != ' ');

        cout << player->get_name()
            << " (Computer) chooses: " << x << " " << y << endl;

        return new Move<char>(x, y, player->get_symbol());
    }

    // ============================
    //   HUMAN PLAY NORMALLY
    // ============================
    while (true)
    {
        cout << player->get_name()
            << " enter row(0-5) column(0-5): ";
        cin >> x >> y;

        if (x >= 0 && x < 6 &&
            y >= 0 && y < 6 &&
            b->get_cell(x, y) == ' ')
            break;

        cout << "Invalid move!\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}


Player<char>* Obstacle6x6_TTT_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}
