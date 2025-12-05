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

// helper: check if 'sym' has a 3-in-row
bool Misere_TTT_Board::check_three(char sym) {
    // rows
    for (int i = 0; i < rows; ++i)
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) return true;
    // cols
    for (int j = 0; j < columns; ++j)
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) return true;
    // diag
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;
    return false;
}

// evaluation: returns score from AI perspective
int Misere_TTT_Board::evaluate_state(char aiSym, char huSym, int depth) {
    // In Misère: whoever makes three loses.
    if (check_three(huSym))  return +10 - depth; // human made three => human lost => AI wins
    if (check_three(aiSym))  return -10 + depth; // AI made three => AI lost
    if (n_moves == rows * columns) return 0; // draw
    return 0; // non-terminal
}

int Misere_TTT_Board::minimax(bool isMaximizing, char aiSym, char huSym, int depth, int alpha, int beta) {
    int score = evaluate_state(aiSym, huSym, depth);
    if (score != 0 || n_moves == rows * columns) { // terminal or draw
        return score;
    }

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == ' ') {
                    // simulate AI move
                    board[i][j] = aiSym;
                    ++n_moves;
                    int val = minimax(false, aiSym, huSym, depth + 1, alpha, beta);
                    // undo move
                    board[i][j] = ' ';
                    --n_moves;
                    best = std::max(best, val);
                    alpha = std::max(alpha, best);
                    if (beta <= alpha) return best; // pruning
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == ' ') {
                    // simulate human move
                    board[i][j] = huSym;
                    ++n_moves;
                    int val = minimax(true, aiSym, huSym, depth + 1, alpha, beta);
                    // undo move
                    board[i][j] = ' ';
                    --n_moves;
                    best = std::min(best, val);
                    beta = std::min(beta, best);
                    if (beta <= alpha) return best; // pruning
                }
            }
        }
        return best;
    }
}

Move<char>* Misere_TTT_Board::get_best_move_for_ai(char aiSym, char huSym) {
    int bestVal = -1000;
    int bestX = -1, bestY = -1;

    // try all empty cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == ' ') {
                // simulate move
                board[i][j] = aiSym;
                ++n_moves;
                int moveVal = minimax(false, aiSym, huSym, 0, -1000, 1000);
                // undo
                board[i][j] = ' ';
                --n_moves;

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

    // fallback (shouldn't happen unless full) → pick any empty cell
    if (bestX == -1) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                if (board[i][j] == ' ') {
                    bestX = i; bestY = j; break;
                }
    }

    return new Move<char>(bestX, bestY, aiSym);
}

bool Misere_TTT_Board::is_win(Player<char>* player) {
	return false; // No direct wins in Misere Tic-Tac-Toe
}

bool Misere_TTT_Board::is_lose(Player<char>* player) {
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
        // Computer player: use smart AI (minimax) via the board
        Board<char>* boardPtr = player->get_board_ptr();
        Misere_TTT_Board* mb = dynamic_cast<Misere_TTT_Board*>(boardPtr);
        if (mb != nullptr) {
            char oppSym = (player->get_symbol() == 'X') ? 'O' : 'X';
            return mb->get_best_move_for_ai(player->get_symbol(), oppSym);
        }
        else {
            // fallback to random if cast fails
            int x, y;
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (boardPtr->get_cell(x, y) != ' ');
            std::cout << "Computer chooses position: " << x << ", " << y << std::endl;
            return new Move<char>(x, y, player->get_symbol());
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}