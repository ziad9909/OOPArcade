#include "Four_in_a_row.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

using namespace std;

Four_in_a_row_board::Four_in_a_row_board() : Board<char>(6,7) {
    srand(static_cast<unsigned int>(time(0)));
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
    return check_win_for_symbol(sym);
}

bool Four_in_a_row_board::check_win_for_symbol(char sym) {
    // Horizontal
    for (int r = 0; r < rows; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == sym && board[r][c+1] == sym &&
                board[r][c+2] == sym && board[r][c+3] == sym)
                return true;

    // Vertical
    for (int c = 0; c < columns; c++)
        for (int r = 0; r <= rows - 4; r++)
            if (board[r][c] == sym && board[r+1][c] == sym &&
                board[r+2][c] == sym && board[r+3][c] == sym)
                return true;

    // Diagonal (top-left to bottom-right)
    for (int r = 0; r <= rows - 4; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == sym && board[r+1][c+1] == sym &&
                board[r+2][c+2] == sym && board[r+3][c+3] == sym)
                return true;

    // Diagonal (bottom-left to top-right)
    for (int r = 3; r < rows; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == sym && board[r-1][c+1] == sym &&
                board[r-2][c+2] == sym && board[r-3][c+3] == sym)
                return true;

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

// ============================================================
// AI IMPLEMENTATION - MINIMAX WITH ALPHA-BETA PRUNING
// ============================================================

vector<int> Four_in_a_row_board::get_valid_columns() {
    vector<int> valid;
    for (int c = 0; c < columns; c++) {
        if (board[0][c] == blank_symbol) {
            valid.push_back(c);
        }
    }
    return valid;
}

int Four_in_a_row_board::count_sequences(char symbol, int length) {
    int count = 0;

    // Helper lambda to check sequence
    auto check_sequence = [&](int r, int c, int dr, int dc) -> bool {
        for (int i = 0; i < length; i++) {
            int nr = r + i * dr;
            int nc = c + i * dc;
            if (nr < 0 || nr >= rows || nc < 0 || nc >= columns) return false;
            if (board[nr][nc] != symbol) return false;
        }
        return true;
    };

    // Check all positions and directions
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            // Horizontal
            if (check_sequence(r, c, 0, 1)) count++;
            // Vertical
            if (check_sequence(r, c, 1, 0)) count++;
            // Diagonal (backslash)
            if (check_sequence(r, c, 1, 1)) count++;
            // Diagonal (forward slash)
            if (check_sequence(r, c, -1, 1)) count++;
        }
    }

    return count;
}

int Four_in_a_row_board::evaluate_board(char aiSymbol) {
    char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';

    // Check for winning condition
    if (check_win_for_symbol(aiSymbol)) return 100000;
    if (check_win_for_symbol(humanSymbol)) return -100000;

    int score = 0;

    // Count AI sequences
    int ai_4 = count_sequences(aiSymbol, 4);
    int ai_3 = count_sequences(aiSymbol, 3);
    int ai_2 = count_sequences(aiSymbol, 2);

    // Count Human sequences
    int human_4 = count_sequences(humanSymbol, 4);
    int human_3 = count_sequences(humanSymbol, 3);
    int human_2 = count_sequences(humanSymbol, 2);

    // Scoring weights
    score += ai_4 * 1000;    // Win
    score += ai_3 * 100;     // Three in a row
    score += ai_2 * 10;      // Two in a row

    score -= human_4 * 1000; // Opponent win
    score -= human_3 * 100;  // Block opponent three
    score -= human_2 * 10;   // Block opponent two

    // Center column preference
    for (int r = 0; r < rows; r++) {
        if (board[r][3] == aiSymbol) score += 3;
    }

    return score;
}

void Four_in_a_row_board::undo_move(int col) {
    for (int row = 0; row < rows; row++) {
        if (board[row][col] != blank_symbol) {
            board[row][col] = blank_symbol;
            n_moves--;
            return;
        }
    }
}

int Four_in_a_row_board::minimax(int depth, bool maximizing, char aiSymbol, char humanSymbol, int alpha, int beta) {
    // Terminal conditions
    if (check_win_for_symbol(aiSymbol)) return 100000 - depth;
    if (check_win_for_symbol(humanSymbol)) return -100000 + depth;
    if (depth == 0 || is_draw(nullptr)) return evaluate_board(aiSymbol);

    vector<int> valid = get_valid_columns();

    if (maximizing) {
        int maxEval = INT_MIN;

        for (int col : valid) {
            // Make move
            for (int row = rows - 1; row >= 0; row--) {
                if (board[row][col] == blank_symbol) {
                    board[row][col] = aiSymbol;
                    n_moves++;

                    int eval = minimax(depth - 1, false, aiSymbol, humanSymbol, alpha, beta);

                    // Undo move
                    board[row][col] = blank_symbol;
                    n_moves--;

                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) break; // Pruning

                    break;
                }
            }
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;

        for (int col : valid) {
            // Make move
            for (int row = rows - 1; row >= 0; row--) {
                if (board[row][col] == blank_symbol) {
                    board[row][col] = humanSymbol;
                    n_moves++;

                    int eval = minimax(depth - 1, true, aiSymbol, humanSymbol, alpha, beta);

                    // Undo move
                    board[row][col] = blank_symbol;
                    n_moves--;

                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) break; // Pruning

                    break;
                }
            }
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

int Four_in_a_row_board::get_best_move(char aiSymbol, char humanSymbol) {
    int bestCol = -1;
    int bestValue = INT_MIN;
    int depth = 6; // Depth of search (adjust for difficulty)

    vector<int> valid = get_valid_columns();

    // Prioritize center column
    auto it = find(valid.begin(), valid.end(), 3);
    if (it != valid.end()) {
        valid.erase(it);
        valid.insert(valid.begin(), 3);
    }

    for (int col : valid) {
        // Make move
        for (int row = rows - 1; row >= 0; row--) {
            if (board[row][col] == blank_symbol) {
                board[row][col] = aiSymbol;
                n_moves++;

                int moveValue = minimax(depth - 1, false, aiSymbol, humanSymbol, INT_MIN, INT_MAX);

                // Undo move
                board[row][col] = blank_symbol;
                n_moves--;

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestCol = col;
                }

                break;
            }
        }
    }

    return bestCol;
}

// ============================================================
// UI IMPLEMENTATION
// ============================================================

Four_in_a_row_Ui::Four_in_a_row_Ui() : UI<char>("Welcome to Four-in-a-Row (Connect 4)", 3) {
    srand(static_cast<unsigned int>(time(0)));
}

Four_in_a_row_Ui::~Four_in_a_row_Ui() {}

Player<char>* Four_in_a_row_Ui::create_player(string &name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** Four_in_a_row_Ui::setup_players() {
    Player<char>** players = new Player<char>*[2];

    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", {"Human", "Computer"});
    players[0] = create_player(name1, 'X', type1);

    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", {"Human", "Computer"});
    players[1] = create_player(name2, 'O', type2);

    return players;
}

Move<char>* Four_in_a_row_Ui::get_move(Player<char>* player) {
    Board<char>* board = player->get_board_ptr();
    int col;

    if (player->get_type() == PlayerType::COMPUTER) {
        cout << "\n[AI] " << player->get_name() << " is thinking...\n";

        char aiSymbol = player->get_symbol();
        char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';

        col = dynamic_cast<Four_in_a_row_board*>(board)->get_best_move(aiSymbol, humanSymbol);

        cout << "[AI] Computer chose column " << col << "\n";
    }
    else {
        do {
            cout << "\n" << player->get_name() << " (" << player->get_symbol()
                 << "), enter column (0-6): ";
            cin >> col;

            if (cin.fail() || col < 0 || col > 6) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "[ERROR] Invalid input! Enter 0-6.\n";
                continue;
            }

            if (board->get_cell(0, col) != '.') {
                cout << "[ERROR] Column full! Choose another.\n";
                continue;
            }

            break;
        } while (true);
    }

    return new Move<char>(0, col, player->get_symbol());
}