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
    n_moves++;
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

int FiveByFive_TTT_Board::count_potential_sequences(char symbol) {
    int count = 0;

    // Check horizontal potential (2 in a row with space to extend)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            int my_pieces = 0;
            int empty_spaces = 0;

            for (int k = 0; k < 3; ++k) {
                if (board[i][j + k] == symbol) my_pieces++;
                else if (board[i][j + k] == ' ') empty_spaces++;
            }

            if (my_pieces == 2 && empty_spaces == 1) count++;
        }
    }

    // Check vertical potential
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j < columns; ++j) {
            int my_pieces = 0;
            int empty_spaces = 0;

            for (int k = 0; k < 3; ++k) {
                if (board[i + k][j] == symbol) my_pieces++;
                else if (board[i + k][j] == ' ') empty_spaces++;
            }

            if (my_pieces == 2 && empty_spaces == 1) count++;
        }
    }

    // Check diagonal (top-left to bottom-right) potential
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            int my_pieces = 0;
            int empty_spaces = 0;

            for (int k = 0; k < 3; ++k) {
                if (board[i + k][j + k] == symbol) my_pieces++;
                else if (board[i + k][j + k] == ' ') empty_spaces++;
            }

            if (my_pieces == 2 && empty_spaces == 1) count++;
        }
    }

    // Check diagonal (top-right to bottom-left) potential
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) {
            int my_pieces = 0;
            int empty_spaces = 0;

            for (int k = 0; k < 3; ++k) {
                if (board[i + k][j - k] == symbol) my_pieces++;
                else if (board[i + k][j - k] == ' ') empty_spaces++;
            }

            if (my_pieces == 2 && empty_spaces == 1) count++;
        }
    }

    return count;
}

// --- AI Functions Implementation ---

int evaluate_board_ai(FiveByFive_TTT_Board* board, char ai_symbol, char opponent_symbol, int depth) {
    auto scores = board->get_sequence_counts();
    int ai_sequences = (ai_symbol == 'X') ? scores.first : scores.second;
    int opp_sequences = (ai_symbol == 'X') ? scores.second : scores.first;

    // Count potential sequences (2 in a row)
    int ai_potential = board->count_potential_sequences(ai_symbol);
    int opp_potential = board->count_potential_sequences(opponent_symbol);

    // Advanced scoring system
    int score = 0;

    // Complete sequences are most important (weight: 1000)
    score += (ai_sequences - opp_sequences) * 1000;

    // Potential sequences (2 in a row) are VERY important (weight: 100)
    score += (ai_potential - opp_potential) * 100;

    // Prefer moves that happen sooner (for more aggressive play)
    score += depth * 10;

    // Strategic position evaluation
    auto board_matrix = board->get_board_matrix();

    // Center control bonus
    if (board_matrix[2][2] == ai_symbol) score += 30;
    else if (board_matrix[2][2] == opponent_symbol) score -= 30;

    // Near-center positions (more important in 5x5)
    vector<pair<int, int>> strategic_positions = {
        {1, 1}, {1, 2}, {1, 3},
        {2, 1}, {2, 3},
        {3, 1}, {3, 2}, {3, 3}
    };

    for (auto& pos : strategic_positions) {
        if (board_matrix[pos.first][pos.second] == ai_symbol) score += 10;
        else if (board_matrix[pos.first][pos.second] == opponent_symbol) score -= 10;
    }

    return score;
}

int minimax_algorithm(FiveByFive_TTT_Board* board, int depth, int alpha, int beta,
    bool is_maximizing, char ai_symbol, char opponent_symbol) {
    // Base cases
    if (depth == 0 || board->get_move_count() >= 24) {
        return evaluate_board_ai(board, ai_symbol, opponent_symbol, depth);
    }

    auto board_matrix = board->get_board_matrix();
    vector<pair<int, int>> available_moves;

    // Find all available moves
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board_matrix[i][j] == ' ') {
                available_moves.push_back({ i, j });
            }
        }
    }

    if (available_moves.empty()) {
        return evaluate_board_ai(board, ai_symbol, opponent_symbol, depth);
    }

    // Move ordering: prioritize center and near-center moves for better pruning
    sort(available_moves.begin(), available_moves.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) {
            int dist_a = abs(a.first - 2) + abs(a.second - 2);
            int dist_b = abs(b.first - 2) + abs(b.second - 2);
            return dist_a < dist_b;
        });

    if (is_maximizing) {
        int max_eval = numeric_limits<int>::min();

        for (auto& move : available_moves) {
            // Create a temporary board for simulation
            FiveByFive_TTT_Board temp_board;
            auto current_board = board->get_board_matrix();

            // Copy current board state
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (current_board[i][j] != ' ') {
                        Move<char> copy_move(i, j, current_board[i][j]);
                        temp_board.update_board(&copy_move);
                    }
                }
            }

            // Make the move
            Move<char> test_move(move.first, move.second, ai_symbol);
            temp_board.update_board(&test_move);

            int eval = minimax_algorithm(&temp_board, depth - 1, alpha, beta, false,
                ai_symbol, opponent_symbol);
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);

            if (beta <= alpha) break; // Alpha-beta pruning
        }
        return max_eval;
    }
    else {
        int min_eval = numeric_limits<int>::max();

        for (auto& move : available_moves) {
            // Create a temporary board for simulation
            FiveByFive_TTT_Board temp_board;
            auto current_board = board->get_board_matrix();

            // Copy current board state
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (current_board[i][j] != ' ') {
                        Move<char> copy_move(i, j, current_board[i][j]);
                        temp_board.update_board(&copy_move);
                    }
                }
            }

            // Make the move
            Move<char> test_move(move.first, move.second, opponent_symbol);
            temp_board.update_board(&test_move);

            int eval = minimax_algorithm(&temp_board, depth - 1, alpha, beta, true,
                ai_symbol, opponent_symbol);
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);

            if (beta <= alpha) break; // Alpha-beta pruning
        }
        return min_eval;
    }
}

pair<int, int> get_best_ai_move(FiveByFive_TTT_Board* board, char ai_symbol, int max_depth) {
    auto board_matrix = board->get_board_matrix();
    vector<pair<int, int>> available_moves;

    // Find all available moves
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board_matrix[i][j] == ' ') {
                available_moves.push_back({ i, j });
            }
        }
    }

    if (available_moves.empty()) {
        return { -1, -1 };
    }

    // For the very first move, prefer center
    if (board->get_move_count() == 0) {
        return { 2, 2 };
    }

    // For early game (first 3 moves), use strategic heuristic
    if (board->get_move_count() < 3) {
        // If center is taken, prefer near-center positions
        if (board_matrix[2][2] != ' ') {
            vector<pair<int, int>> good_positions = {
                {1, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 3}, {3, 1}, {3, 2}, {3, 3}
            };
            for (auto& pos : good_positions) {
                if (board_matrix[pos.first][pos.second] == ' ') {
                    return pos;
                }
            }
        }
    }

    char opponent_symbol = (ai_symbol == 'X') ? 'O' : 'X';
    int best_score = numeric_limits<int>::min();
    pair<int, int> best_move = available_moves[0];

    // Try each available move
    for (auto& move : available_moves) {
        // Create a temporary board for simulation
        FiveByFive_TTT_Board temp_board;
        auto current_board = board->get_board_matrix();

        // Copy current board state
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (current_board[i][j] != ' ') {
                    Move<char> copy_move(i, j, current_board[i][j]);
                    temp_board.update_board(&copy_move);
                }
            }
        }

        // Make the move
        Move<char> test_move(move.first, move.second, ai_symbol);
        temp_board.update_board(&test_move);

        // Evaluate this move
        int score = minimax_algorithm(&temp_board, max_depth, numeric_limits<int>::min(),
            numeric_limits<int>::max(), false, ai_symbol, opponent_symbol);

        if (score > best_score) {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}

// --- FiveByFive_TTT_UI Implementation ---

FiveByFive_TTT_UI::FiveByFive_TTT_UI()
    : UI<char>(
        "\n"
        "=====================================================\n"
        "            WELCOME TO 5 x 5 TIC-TAC-TOE\n"
        "=====================================================\n",
        3
    )
{
    srand(time(0));
}

Player<char>* FiveByFive_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "smart AI")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Player<char>** FiveByFive_TTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Smart AI" };

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
        // Smart AI player using Minimax

        FiveByFive_TTT_Board* board = dynamic_cast<FiveByFive_TTT_Board*>(player->get_board_ptr());

        // Get best move using AI helper function with depth 3
        pair<int, int> best_move = get_best_ai_move(board, player->get_symbol(), 3);

        x = best_move.first;
        y = best_move.second;

        cout << "Smart AI chose position (" << x << ", " << y << ")\n";
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