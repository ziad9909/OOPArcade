#include "Diamond_TTT_Classes.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>   // For abs()

using namespace std;

// ============================================================================
// DIAMOND_TTT_BOARD IMPLEMENTATION (7x7)
// ============================================================================

/**
 * @brief Construct a new Diamond_TTT_Board object
 * @details Initializes the 7x7 diamond-shaped board.
 */
Diamond_TTT_Board::Diamond_TTT_Board() : Board<char>(7, 7) {
    valid_cells.clear();

    int mid = rows / 2; // rows == 7 now

    // Initialize all cells to spaces
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            board[i][j] = ' ';

    // Build valid_cells using diamond rule: |r-mid| + |c-mid| <= mid
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (std::abs(r - mid) + std::abs(c - mid) <= mid) {
                valid_cells.push_back({ r, c });
            }
            else {
                // Mark invalid cells with '.'
                board[r][c] = '.';
            }
        }
    }
}

/**
 * @brief Check if coordinates are part of the diamond
 */
bool Diamond_TTT_Board::is_valid_cell(int x, int y) const {
    for (const auto& cell : valid_cells)
        if (cell.first == x && cell.second == y) return true;
    return false;
}

/**
 * @brief Updates the board with a move
 */
bool Diamond_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid coordinates! Must be between 0-6.\n";
        return false;
    }

    if (!is_valid_cell(x, y)) {
        cout << "Cell (" << x << "," << y << ") is not in diamond shape!\n";
        return false;
    }

    if (board[x][y] != ' ') {
        cout << "Cell (" << x << "," << y << ") already has '" << board[x][y] << "'!\n";
        return false;
    }

    board[x][y] = sym;
    n_moves++;
    return true;
}

/**
 * @brief Undo a move (restore cell to empty)
 */
void Diamond_TTT_Board::undo_move(int x, int y) {
    board[x][y] = ' ';
    n_moves--;
}

/**
 * @brief Get all empty cells (for AI)
 */
vector<pair<int, int>> Diamond_TTT_Board::get_empty_cells() const {
    vector<pair<int, int>> empty;
    for (const auto& cell : valid_cells)
        if (board[cell.first][cell.second] == ' ')
            empty.push_back(cell);
    return empty;
}

/**
 * @brief Validate move without applying it
 */
string Diamond_TTT_Board::validate_move(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return "Coordinates must be 0-6!";
    if (!is_valid_cell(x, y))
        return "Not a diamond cell!";
    if (board[x][y] != ' ') {
        string msg = "Cell occupied by '";
        msg += board[x][y];
        msg += "'!";
        return msg;
    }
    return "";
}

/**
 * @brief Check if player has won
 */
 /**
  * @brief Check if player has won - Simplified and optimized
  */
bool Diamond_TTT_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    // Get all possible lines
    auto all_lines = get_all_lines();

    // Separate 3-lines and 4-lines completed by the player
    vector<vector<pair<int, int>>> completed_3lines;
    vector<vector<pair<int, int>>> completed_4lines;

    for (const auto& line : all_lines) {
        bool complete = true;
        for (const auto& cell : line) {
            if (board[cell.first][cell.second] != symbol) {
                complete = false;
                break;
            }
        }

        if (complete) {
            if (line.size() == 3) {
                completed_3lines.push_back(line);
            }
            else if (line.size() == 4) {
                completed_4lines.push_back(line);
            }
        }
    }

    // If we don't have at least one of each type, can't win
    if (completed_3lines.empty() || completed_4lines.empty()) {
        return false;
    }

    // Debug output to see what lines were found
    if (false) {  // Set to true for debugging
        cout << "\nDEBUG: Player " << symbol << " has "
            << completed_3lines.size() << " completed 3-lines and "
            << completed_4lines.size() << " completed 4-lines\n";
    }

    // Check if any 3-line and 4-line share exactly one cell and have different directions
    for (const auto& line3 : completed_3lines) {
        // Determine direction of 3-line
        string dir3 = get_line_direction(line3);

        for (const auto& line4 : completed_4lines) {
            // Determine direction of 4-line
            string dir4 = get_line_direction(line4);

            // Must be different directions
            if (dir3 == dir4) continue;

            // Count shared cells
            int shared = 0;
            for (const auto& cell3 : line3) {
                for (const auto& cell4 : line4) {
                    if (cell3.first == cell4.first && cell3.second == cell4.second) {
                        shared++;
                        break;
                    }
                }
            }

            if (shared == 1) {
                return true;  // Win condition met!
            }
        }
    }

    return false;
}

string Diamond_TTT_Board::get_line_direction(const vector<pair<int, int>>& line) {
    if (line.size() < 2) return "unknown";

    int dx = line[1].first - line[0].first;
    int dy = line[1].second - line[0].second;

    // Normalize to -1, 0, or 1
    if (dx != 0) dx /= abs(dx);
    if (dy != 0) dy /= abs(dy);

    if (dx == 0 && dy == 1) return "horizontal";
    if (dx == 1 && dy == 0) return "vertical";
    if (dx == 1 && dy == 1) return "diagonal_down";
    if (dx == 1 && dy == -1) return "diagonal_up";

    return "unknown";
}

/**
 * @brief Check if game is draw
 */
bool Diamond_TTT_Board::is_draw(Player<char>* player) {
    // Check if any empty cell exists
    for (const auto& cell : valid_cells)
        if (board[cell.first][cell.second] == ' ') return false;

    // No empty cells and no winner = draw
    return !is_win(player);
}

/**
 * @brief Check if game is over (win or draw)
 */
bool Diamond_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Debug helper: print win status
 */
void Diamond_TTT_Board::debug_win_check(Player<char>* player) {
    cout << "\n=== DEBUG for Player " << player->get_symbol() << " ===\n";
    if (is_win(player)) cout << "PLAYER WINS!\n";
    else cout << "Not winning yet.\n";
}

/**
 * @brief Get line cells starting from (start_x,start_y) in direction (dx,dy)
 */
vector<pair<int, int>> Diamond_TTT_Board::get_line_cells(int start_x, int start_y,
    int dx, int dy, int length) {
    vector<pair<int, int>> line;
    int x = start_x, y = start_y;
    for (int i = 0; i < length; i++) {
        if (x >= 0 && x < rows && y >= 0 && y < columns && is_valid_cell(x, y))
            line.push_back({ x, y });
        else return {};
        x += dx;
        y += dy;
    }
    return line;
}

/**
 * @brief Generate all possible winning lines (3 and 4) dynamically for 7x7 diamond
 */
vector<vector<pair<int, int>>> Diamond_TTT_Board::get_all_lines() {
    vector<vector<pair<int, int>>> all_lines;

    const int dirs[4][2] = {
        {1, 0},  // vertical
        {0, 1},  // horizontal
        {1, 1},  // main diagonal
        {1,-1}   // anti diagonal
    };

    const int lengths[2] = { 3, 4 };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (!is_valid_cell(r, c)) continue;

            for (const auto& d : dirs) {
                int dx = d[0], dy = d[1];

                for (int L : lengths) {
                    vector<pair<int, int>> line;
                    int nr = r, nc = c;
                    bool ok = true;

                    for (int k = 0; k < L; k++) {
                        if (!is_valid_cell(nr, nc)) {
                            ok = false;
                            break;
                        }
                        line.push_back({ nr, nc });
                        nr += dx;
                        nc += dy;
                    }

                    if (ok) all_lines.push_back(line);
                }
            }
        }
    }

    return all_lines;
}

// ============================================================================
// DIAMOND_TTT_UI IMPLEMENTATION
// ============================================================================

Diamond_TTT_UI::Diamond_TTT_UI() : UI<char>("=== Diamond Tic-Tac-Toe ===", 3) {}

/**
 * @brief Set up two players
 */
Player<char>** Diamond_TTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

/**
 * @brief Create a player object
 */
Player<char>* Diamond_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Evaluate board for AI
 */
int Diamond_TTT_UI::evaluate_board(Diamond_TTT_Board* board, char ai_symbol, char opponent_symbol) {
    Player<char> ai("AI", ai_symbol, PlayerType::COMPUTER);
    Player<char> opp("OPP", opponent_symbol, PlayerType::HUMAN);

    if (board->is_win(&ai)) return 10;
    if (board->is_win(&opp)) return -10;
    return 0;
}

int Diamond_TTT_UI::minimax_helper(Diamond_TTT_Board* board,
    char current_symbol,
    char ai_symbol,
    char opponent_symbol,
    bool isMaximizing,
    int depth)
{
    int score = evaluate_board(board, ai_symbol, opponent_symbol);

    if (score == 10 || score == -10)
        return score;

    if (board->get_empty_cells().empty())
        return 0;

    if (depth == 0)
        return score;

    if (isMaximizing) {
        int bestVal = INT_MIN;

        auto empty_cells = board->get_empty_cells();
        for (auto cell : empty_cells) {
            // use stack Move to avoid leaking memory
            Move<char> tmp(cell.first, cell.second, current_symbol);
            board->update_board(&tmp);

            int value = minimax_helper(board,
                opponent_symbol,
                ai_symbol,
                opponent_symbol,
                false,
                depth - 1);

            board->undo_move(cell.first, cell.second);
            bestVal = max(bestVal, value);
        }
        return bestVal;
    }
    else {
        int bestVal = INT_MAX;

        auto empty_cells = board->get_empty_cells();
        for (auto cell : empty_cells) {
            Move<char> tmp(cell.first, cell.second, current_symbol);
            board->update_board(&tmp);

            int value = minimax_helper(board,
                ai_symbol,
                ai_symbol,
                opponent_symbol,
                true,
                depth - 1);

            board->undo_move(cell.first, cell.second);
            bestVal = min(bestVal, value);
        }
        return bestVal;
    }
}

/**
 * @brief Minimax algorithm - matches header file signature
 */
int Diamond_TTT_UI::minimax(Diamond_TTT_Board* board,
    char current_symbol,
    char ai_symbol,
    char opponent_symbol,
    bool isMaximizing,
    int depth)
{
    int search_depth = depth;

    if (search_depth == 0) {
        int empty_count = board->get_empty_cells().size();

        if (empty_count >= 12) search_depth = 3;
        else if (empty_count >= 8) search_depth = 4;
        else if (empty_count >= 5) search_depth = 5;
        else search_depth = 6;
    }

    return minimax_helper(board,
        current_symbol,
        ai_symbol,
        opponent_symbol,
        isMaximizing,
        search_depth);
}

/**
 * @brief Find best move for AI
 */
pair<int, int> Diamond_TTT_UI::find_best_move(Diamond_TTT_Board* board, char ai_symbol, char opponent_symbol) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = { -1, -1 };

    auto empty_cells = board->get_empty_cells();

    // If there are too many empty cells, use a heuristic
    if (empty_cells.size() > 10) {
        // Prefer cells closer to center first (heuristic)
        int mid = board->get_rows() / 2; // assume Board has get_rows(); if not, use board->rows directly
        // If get_rows() not available, fallback:
        if (mid <= 0) mid = 3;

        vector<pair<int, int>> sorted_cells = empty_cells;
        sort(sorted_cells.begin(), sorted_cells.end(),
            [mid](const pair<int, int>& a, const pair<int, int>& b) {
                int da = abs(a.first - mid) + abs(a.second - mid);
                int db = abs(b.first - mid) + abs(b.second - mid);
                return da < db;
            });

        // Check for winning move
        for (auto cell : empty_cells) {
            Move<char> tmp(cell.first, cell.second, ai_symbol);
            board->update_board(&tmp);
            Player<char> temp_ai("AI", ai_symbol, PlayerType::COMPUTER);
            if (board->is_win(&temp_ai)) {
                board->undo_move(cell.first, cell.second);
                return cell;
            }
            board->undo_move(cell.first, cell.second);
        }

        // Check for blocking opponent's winning move
        for (auto cell : empty_cells) {
            Move<char> tmp(cell.first, cell.second, opponent_symbol);
            board->update_board(&tmp);
            Player<char> temp_opp("OPP", opponent_symbol, PlayerType::COMPUTER);
            if (board->is_win(&temp_opp)) {
                board->undo_move(cell.first, cell.second);
                return cell;
            }
            board->undo_move(cell.first, cell.second);
        }

        // Prefer center cells (from sorted list)
        for (auto cell : sorted_cells) {
            if (board->validate_move(cell.first, cell.second).empty()) {
                return cell;
            }
        }

        // Otherwise, return first available cell
        if (!empty_cells.empty()) {
            return empty_cells[0];
        }
    }

    // For fewer empty cells, use minimax
    for (auto cell : empty_cells) {
        Move<char> tmp(cell.first, cell.second, ai_symbol);
        board->update_board(&tmp);
        int moveVal = minimax(board, opponent_symbol, ai_symbol, opponent_symbol, false);
        board->undo_move(cell.first, cell.second);

        if (moveVal > bestVal) {
            bestVal = moveVal;
            bestMove = cell;
        }

        // If we find a winning move, take it immediately
        if (moveVal == 10) {
            break;
        }
    }

    // If no good move found, pick first available
    if (bestMove.first == -1 && !empty_cells.empty()) {
        bestMove = empty_cells[0];
    }

    return bestMove;
}

/**
 * @brief Get a move from player (human input or AI)
 */
Move<char>* Diamond_TTT_UI::get_move(Player<char>* player) {
    int x, y;
    Diamond_TTT_Board* board = dynamic_cast<Diamond_TTT_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        bool valid_move = false;
        while (!valid_move) {
            cout << "\n" << player->get_name() << " (" << player->get_symbol()
                << "), enter your move (row column): ";
            if (!(cin >> x >> y)) {
                cout << "Invalid input! Enter two numbers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            string error = board->validate_move(x, y);
            if (!error.empty()) {
                cout << "Error: " << error << "\n";
                continue;
            }
            valid_move = true;
        }
    }
    else {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() << ") is thinking...\n";

        char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
        auto best_move = find_best_move(board, player->get_symbol(), opponent_symbol);
        x = best_move.first;
        y = best_move.second;
        cout << player->get_name() << " (" << player->get_symbol() << ") chooses: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Display board
 */
 /**
  * @brief Display board with properly aligned column numbers
  */
void Diamond_TTT_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    int rows = matrix.size();
    if (rows == 0) return;
    int columns = matrix[0].size();

    cout << "\n=== Diamond Tic-Tac-Toe ===\n\n";

    // Print column headers with proper spacing
    cout << "     ";
    for (int j = 0; j < columns; j++) {
        cout << setw(3) << j << " ";
    }
    cout << endl;

    // Print top border
    cout << "    ";
    for (int j = 0; j < columns; j++) {
        cout << "----";
    }
    cout << "-" << endl;

    // Print each row with row numbers
    for (int i = 0; i < rows; i++) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < columns; j++) {
            cout << setw(3) << matrix[i][j] << "|";
        }
        cout << endl;

        // Print row separator
        cout << "    ";
        for (int j = 0; j < columns; j++) {
            cout << "----";
        }
        cout << "-" << endl;
    }
    cout << "\nNote: '.' marks invalid cells (not part of diamond shape)\n";
}
