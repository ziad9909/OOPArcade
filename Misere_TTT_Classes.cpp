#include "Misere_TTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Misere_TTT_Board implementations
Misere_TTT_Board::Misere_TTT_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';
}

bool Misere_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        std::cout << "Invalid position! Please enter a valid row and column.\n";
        return false;
    }

    if (board[x][y] != ' ') {
        std::cout << "Cell already occupied! Choose another position.\n";
        return false;
    }

    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

bool Misere_TTT_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    // Check rows
    for (int i = 0; i < rows; i++)
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
    // Columns
    for (int j = 0; j < columns; j++)
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym)
            return true;
    // Diagonals
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;
    return false;
}

bool Misere_TTT_Board::is_lose(Player<char>* player) {
    return is_win(player);
}

bool Misere_TTT_Board::is_draw(Player<char>* player) {
    return n_moves == rows * columns && !is_win(player);
}

bool Misere_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// Misere_TTT_UI implementations
Misere_TTT_UI::Misere_TTT_UI() : UI<char>("Welcome to Misere Tic-Tac-Toe", 3) {
    srand(time(0));
}

Player<char>* Misere_TTT_UI::create_player(std::string& name, char symbol, PlayerType type) {
    std::cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_TTT_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        std::cout << player->get_name() << "'s turn (" << player->get_symbol()
            << "): Enter row and column (0-2): ";
        std::cin >> x >> y;
    }
    else {
        // Computer player
        Board<char>* board = player->get_board_ptr();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_cell(x, y) != ' ');

        std::cout << "Computer chooses position: " << x << ", " << y << std::endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}