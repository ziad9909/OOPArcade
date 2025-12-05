#include "Ultimate_TTT_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <tuple>

using namespace std;

Ultimate_TTT_Board::Ultimate_TTT_Board() : Board(9, 9) {
    // Initialize main board (3x3)
    main_board = vector<vector<char>>(3, vector<char>(3, blank_symbol));
    
    // Initialize 9 sub-boards (each 3x3)
    sub_boards = vector<vector<vector<vector<char>>>>(3, 
        vector<vector<vector<char>>>(3, 
            vector<vector<char>>(3, 
                vector<char>(3, blank_symbol))));
    
    // Initialize move counters for each sub-board
    sub_board_moves = vector<vector<int>>(3, vector<int>(3, 0));
    
    // First move can be on any sub-board
    active_main_row = -1;
    active_main_col = -1;
    
    // Initialize the main board representation (for compatibility)
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

char Ultimate_TTT_Board::check_sub_board_win(int main_r, int main_c) {
    const auto& sub = sub_boards[main_r][main_c];
    
    // Helper lambda to check if three cells are equal and not blank
    auto all_equal = [&](int r1, int c1, int r2, int c2, int r3, int c3) {
        return sub[r1][c1] == sub[r2][c2] && 
               sub[r2][c2] == sub[r3][c3] && 
               sub[r1][c1] != blank_symbol;
    };
    
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (all_equal(i, 0, i, 1, i, 2)) {
            return sub[i][0];
        }
    }
    
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (all_equal(0, j, 1, j, 2, j)) {
            return sub[0][j];
        }
    }
    
    // Check diagonals
    if (all_equal(0, 0, 1, 1, 2, 2)) {
        return sub[1][1];
    }
    if (all_equal(0, 2, 1, 1, 2, 0)) {
        return sub[1][1];
    }
    
    return blank_symbol; // No winner
}

bool Ultimate_TTT_Board::is_sub_board_full(int main_r, int main_c) {
    return sub_board_moves[main_r][main_c] == 9;
}

bool Ultimate_TTT_Board::is_sub_board_available(int main_r, int main_c) {
    // Sub-board is available if it's not won and not full
    return main_board[main_r][main_c] == blank_symbol && 
           !is_sub_board_full(main_r, main_c);
}

pair<int, int> Ultimate_TTT_Board::get_active_sub_board() {
    return make_pair(active_main_row, active_main_col);
}

vector<vector<char>> Ultimate_TTT_Board::get_sub_board(int main_r, int main_c) const {
    return sub_boards[main_r][main_c];
}

tuple<int, int, int, int> Ultimate_TTT_Board::convert_coordinates(int global_x, int global_y) {
    int main_row = global_x / 3;
    int main_col = global_y / 3;
    int sub_row = global_x % 3;
    int sub_col = global_y % 3;
    return make_tuple(main_row, main_col, sub_row, sub_col);
}

bool Ultimate_TTT_Board::update_board(Move<char>* move) {
    int global_x = move->get_x();
    int global_y = move->get_y();
    char mark = move->get_symbol();
    
    // Validate global coordinates
    if (global_x < 0 || global_x >= 9 || global_y < 0 || global_y >= 9) {
        return false;
    }
    
    // Convert to main and sub coordinates
    int main_r, main_c, sub_r, sub_c;
    tie(main_r, main_c, sub_r, sub_c) = convert_coordinates(global_x, global_y);
    
    // Check if this sub-board is the active one (or if any sub-board is allowed)
    if (active_main_row != -1 && active_main_col != -1) {
        if (main_r != active_main_row || main_c != active_main_col) {
            cout << "Invalid move! You must play in sub-board (" 
                 << active_main_row << ", " << active_main_col << ")\n";
            return false;
        }
    }
    
    // Check if sub-board is available
    if (!is_sub_board_available(main_r, main_c)) {
        cout << "Invalid move! Sub-board (" << main_r << ", " << main_c 
             << ") is already won or full.\n";
        return false;
    }
    
    // Check if cell in sub-board is empty
    if (sub_boards[main_r][main_c][sub_r][sub_c] != blank_symbol) {
        cout << "Invalid move! Cell already occupied.\n";
        return false;
    }
    
    // Make the move
    sub_boards[main_r][main_c][sub_r][sub_c] = toupper(mark);
    sub_board_moves[main_r][main_c]++;
    n_moves++;
    
    // Update main board representation (for compatibility)
    board[global_x][global_y] = toupper(mark);
    
    // Check if this sub-board has a winner
    char winner = check_sub_board_win(main_r, main_c);
    if (winner != blank_symbol) {
        main_board[main_r][main_c] = winner;
        cout << "\n*** Sub-board (" << main_r << ", " << main_c 
             << ") won by " << winner << "! ***\n";
    } else if (is_sub_board_full(main_r, main_c)) {
        // Sub-board is full but no winner (draw)
        main_board[main_r][main_c] = 'D'; // Mark as drawn
        cout << "\n*** Sub-board (" << main_r << ", " << main_c 
             << ") ended in a draw ***\n";
    }
    
    // Determine next active sub-board
    // If the target sub-board (determined by sub_r, sub_c) is available, use it
    // Otherwise, player can choose any available sub-board
    if (is_sub_board_available(sub_r, sub_c)) {
        active_main_row = sub_r;
        active_main_col = sub_c;
    } else {
        // Target sub-board is won or full, player can choose any available
        active_main_row = -1;
        active_main_col = -1;
    }
    
    return true;
}

bool Ultimate_TTT_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    
    // Check if player has won three sub-boards in a row on main board
    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a == sym;
    };
    
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (all_equal(main_board[i][0], main_board[i][1], main_board[i][2])) {
            return true;
        }
    }
    
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (all_equal(main_board[0][j], main_board[1][j], main_board[2][j])) {
            return true;
        }
    }
    
    // Check diagonals
    if (all_equal(main_board[0][0], main_board[1][1], main_board[2][2])) {
        return true;
    }
    if (all_equal(main_board[0][2], main_board[1][1], main_board[2][0])) {
        return true;
    }
    
    return false;
}

bool Ultimate_TTT_Board::is_draw(Player<char>* player) {
    // Check if all sub-boards are won/drawn and no main board winner
    bool all_claimed = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (main_board[i][j] == blank_symbol) {
                all_claimed = false;
                break;
            }
        }
        if (!all_claimed) break;
    }
    
    return all_claimed && !is_win(player);
}

bool Ultimate_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ============================================================
// UI IMPLEMENTATION
// ============================================================

Ultimate_TTT_UI::Ultimate_TTT_UI() : UI<char>("Welcome to Ultimate Tic Tac Toe!", 3) {
    srand(static_cast<unsigned int>(time(0)));
    ultimate_board_ptr = nullptr;
}

Player<char>* Ultimate_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    
    return new Player<char>(name, symbol, type);
}

void Ultimate_TTT_UI::display_ultimate_board(Ultimate_TTT_Board* board) {
    cout << "\n";
    cout << "==========================================\n";
    cout << "      ULTIMATE TIC TAC TOE BOARD\n";
    cout << "==========================================\n\n";
    
    // Display main board status
    cout << "Main Board Status (won sub-boards):\n";
    cout << "   ";
    for (int j = 0; j < 3; j++) {
        cout << setw(3) << j;
    }
    cout << "\n";
    
    for (int i = 0; i < 3; i++) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < 3; j++) {
            char status = board->get_main_board()[i][j];
            if (status == '.') {
                cout << setw(3) << ".";
            } else if (status == 'D') {
                cout << setw(3) << "D";
            } else {
                cout << setw(3) << status;
            }
        }
        cout << "\n";
    }
    cout << "\n";
    
    // Display all 9 sub-boards
    for (int main_r = 0; main_r < 3; main_r++) {
        // Print sub-board rows
        for (int sub_r = 0; sub_r < 3; sub_r++) {
            for (int main_c = 0; main_c < 3; main_c++) {
                auto sub_board = board->get_sub_board(main_r, main_c);
                
                // Print row of this sub-board
                cout << " ";
                for (int sub_c = 0; sub_c < 3; sub_c++) {
                    char cell = sub_board[sub_r][sub_c];
                    if (cell == '.') {
                        cout << " .";
                    } else {
                        cout << " " << cell;
                    }
                }
                cout << " |";
            }
            cout << "\n";
        }
        
        // Print separator between main board rows
        if (main_r < 2) {
            for (int main_c = 0; main_c < 3; main_c++) {
                cout << " ------- |";
            }
            cout << "\n";
        }
    }
    
    // Show active sub-board
    auto active = board->get_active_sub_board();
    if (active.first == -1) {
        cout << "\nActive Sub-Board: You can choose any available sub-board\n";
    } else {
        cout << "\nActive Sub-Board: (" << active.first << ", " << active.second << ")\n";
    }
    cout << "\n";
}

void Ultimate_TTT_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    // Display the ultimate board if we have the pointer
    if (ultimate_board_ptr != nullptr) {
        // We need to cast away const to call display_ultimate_board
        // This is safe because we're only displaying, not modifying
        const_cast<Ultimate_TTT_UI*>(this)->display_ultimate_board(ultimate_board_ptr);
    } else {
        // Fallback to simple display
        UI<char>::display_board_matrix(matrix);
    }
}

void Ultimate_TTT_UI::set_board_ptr(Ultimate_TTT_Board* board) {
    ultimate_board_ptr = board;
}

Move<char>* Ultimate_TTT_UI::get_move(Player<char>* player) {
    Board<char>* board_ptr = player->get_board_ptr();
    Ultimate_TTT_Board* ultimate_board = dynamic_cast<Ultimate_TTT_Board*>(board_ptr);
    
    if (!ultimate_board) {
        cout << "Error: Invalid board type\n";
        return nullptr;
    }
    
    // Store board pointer for display_board_matrix
    if (ultimate_board_ptr != ultimate_board) {
        set_board_ptr(ultimate_board);
    }
    
    // Display the board
    display_ultimate_board(ultimate_board);
    
    int global_x, global_y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        auto active = ultimate_board->get_active_sub_board();
        
        if (active.first == -1) {
            cout << player->get_name() << " (" << player->get_symbol() 
                 << "), you can play on any available sub-board.\n";
            cout << "Enter global coordinates (row col) from 0-8: ";
        } else {
            cout << player->get_name() << " (" << player->get_symbol() 
                 << "), you must play in sub-board (" 
                 << active.first << ", " << active.second << ").\n";
            cout << "Enter local coordinates within that sub-board (row col) from 0-2: ";
        }
        
        cin >> global_x >> global_y;
        
        // If active sub-board is specified, convert local to global
        if (active.first != -1 && active.second != -1) {
            global_x = active.first * 3 + global_x;
            global_y = active.second * 3 + global_y;
        }
    }
    else {
        // Computer player - make random valid move
        cout << "\n[AI] " << player->get_name() << " is thinking...\n";
        
        auto active = ultimate_board->get_active_sub_board();
        vector<pair<int, int>> valid_moves;
        
        if (active.first == -1) {
            // Can play on any available sub-board
            for (int main_r = 0; main_r < 3; main_r++) {
                for (int main_c = 0; main_c < 3; main_c++) {
                    if (ultimate_board->is_sub_board_available(main_r, main_c)) {
                        auto sub = ultimate_board->get_sub_board(main_r, main_c);
                        for (int sub_r = 0; sub_r < 3; sub_r++) {
                            for (int sub_c = 0; sub_c < 3; sub_c++) {
                                if (sub[sub_r][sub_c] == '.') {
                                    int gx = main_r * 3 + sub_r;
                                    int gy = main_c * 3 + sub_c;
                                    valid_moves.push_back({gx, gy});
                                }
                            }
                        }
                    }
                }
            }
        } else {
            // Must play in specific sub-board
            auto sub = ultimate_board->get_sub_board(active.first, active.second);
            for (int sub_r = 0; sub_r < 3; sub_r++) {
                for (int sub_c = 0; sub_c < 3; sub_c++) {
                    if (sub[sub_r][sub_c] == '.') {
                        int gx = active.first * 3 + sub_r;
                        int gy = active.second * 3 + sub_c;
                        valid_moves.push_back({gx, gy});
                    }
                }
            }
        }
        
        if (valid_moves.empty()) {
            cout << "[AI] No valid moves available!\n";
            return nullptr;
        }
        
        // Pick random valid move
        auto move = valid_moves[rand() % valid_moves.size()];
        global_x = move.first;
        global_y = move.second;
        
        cout << "[AI] Computer chose position: (" << global_x << ", " << global_y << ")\n";
    }
    
    return new Move<char>(global_x, global_y, player->get_symbol());
}

