#include "FiveByFiveTTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// --- FiveByFive_TTT_Board Implementation ---

FiveByFive_TTT_Board::FiveByFive_TTT_Board() : Board(5, 5) {
    // Initialize the board with spaces (empty cells)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
        }
    }
}

bool FiveByFive_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if position is valid
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position. Row and column must be between 0 and 4.\n";
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != ' ') {
        cout << "Cell (" << x << ", " << y << ") is already occupied. Try again.\n";
        return false;
    }

    // Check if symbol is valid
    if (symbol != 'X' && symbol != 'O') {
        cout << "Invalid symbol. Must be X or O.\n";
        return false;
    }

    // Apply the move
    board[x][y] = symbol;
    n_moves++; // This is OK because we're in the derived class
    return true;
}

bool FiveByFive_TTT_Board::is_draw(Player<char>* player) {
    // Game is a draw if board is full (24 moves made) and scores are equal
    if (get_move_count() < 24) return false;

    auto scores = get_sequence_counts();
    return scores.first == scores.second;
}

bool FiveByFive_TTT_Board::is_win(Player<char>* player) {
    if (get_move_count() < 24) return false; // Game not finished yet

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int current_score = count_sequences(current_symbol);
    int opponent_score = count_sequences(opponent_symbol);

    return current_score > opponent_score;
}

bool FiveByFive_TTT_Board::is_lose(Player<char>* player) {
    if (get_move_count() < 24) return false; // Game not finished yet

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int current_score = count_sequences(current_symbol);
    int opponent_score = count_sequences(opponent_symbol);

    return current_score < opponent_score;
}

bool FiveByFive_TTT_Board::game_is_over(Player<char>* player) {
    // Game is over when 24 moves are made (all but one cell filled)
    return get_move_count() >= 24;
}

pair<int, int> FiveByFive_TTT_Board::get_sequence_counts() {
    int x_count = count_sequences('X');
    int o_count = count_sequences('O');
    return make_pair(x_count, o_count);
}

int FiveByFive_TTT_Board::count_sequences(char symbol) {
    int count = 0;

    // Check horizontal sequences
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == symbol &&
                board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check vertical sequences
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == symbol &&
                board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == symbol &&
                board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == symbol &&
                board[i + 1][j - 1] == symbol &&
                board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }

    return count;
}

// --- FiveByFive_TTT_UI Implementation ---

FiveByFive_TTT_UI::FiveByFive_TTT_UI()
    : UI<char>("Welcome to 5x5 Tic-Tac-Toe! Get the most three-in-a-row sequences!", 3) {
    srand(time(0));
}

Player<char>* FiveByFive_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Player<char>** FiveByFive_TTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // Player X
    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    // Player O
    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Move<char>* FiveByFive_TTT_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), your turn.\n";
        cout << "Enter row and column (0-4): ";
        cin >> x >> y;
    }
    else {
        // COMPUTER player (Random)
        cout << "Computer player " << player->get_name() << " is thinking...\n";

        FiveByFive_TTT_Board* board = dynamic_cast<FiveByFive_TTT_Board*>(player->get_board_ptr());
        auto board_matrix = board->get_board_matrix();

        // Find all empty cells
        vector<pair<int, int>> empty_cells;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board_matrix[i][j] == ' ') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        // Pick a random empty cell
        if (!empty_cells.empty()) {
            int random_index = rand() % empty_cells.size();
            x = empty_cells[random_index].first;
            y = empty_cells[random_index].second;
        }
        else {
            x = y = 0; // Fallback (shouldn't happen)
        }

        cout << "Computer chose position (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

void FiveByFive_TTT_UI::run_game_with_custom_loop(FiveByFive_TTT_Board* board, Player<char>* players[2]) {
    display_board_matrix(board->get_board_matrix());

    Player<char>* currentPlayer = players[0];
    int playerIndex = 0;

    // Play exactly 24 moves (all but one cell)
    while (board->get_move_count() < 24) {
        currentPlayer = players[playerIndex];
        Move<char>* move = get_move(currentPlayer);

        while (!board->update_board(move)) {
            delete move;
            move = get_move(currentPlayer);
        }

        delete move;
        display_board_matrix(board->get_board_matrix());

        // Display current sequence counts
        auto scores = board->get_sequence_counts();
        cout << "Current scores - X: " << scores.first << " sequences, O: " << scores.second << " sequences\n";
        cout << "Moves made: " << board->get_move_count() << "/24\n\n";

        // Switch player
        playerIndex = 1 - playerIndex;
    }

    // Game finished - determine winner
    auto final_scores = board->get_sequence_counts();
    cout << "\n=== GAME OVER ===\n";
    cout << "Final scores:\n";
    cout << players[0]->get_name() << " (X): " << final_scores.first << " sequences\n";
    cout << players[1]->get_name() << " (O): " << final_scores.second << " sequences\n";

    if (final_scores.first > final_scores.second) {
        cout << players[0]->get_name() << " (X) wins!\n";
    }
    else if (final_scores.second > final_scores.first) {
        cout << players[1]->get_name() << " (O) wins!\n";
    }
    else {
        cout << "It's a draw!\n";
    }
}