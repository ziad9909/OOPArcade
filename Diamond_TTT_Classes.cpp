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
// DIAMOND_TTT_BOARD IMPLEMENTATION
// ============================================================================

/**
 * @brief Construct a new Diamond_TTT_Board object
 * @details Initializes the 5x5 diamond-shaped board.
 * Invalid cells are marked with '.' and valid cells are stored in valid_cells.
 */
Diamond_TTT_Board::Diamond_TTT_Board() : Board<char>(5, 5) {
    valid_cells.clear();

    // Row 0: only center column
    valid_cells.push_back({ 0, 2 });

    // Row 1: three middle columns  
    valid_cells.push_back({ 1, 1 });
    valid_cells.push_back({ 1, 2 });
    valid_cells.push_back({ 1, 3 });

    // Row 2: all five columns
    for (int j = 0; j < 5; j++) valid_cells.push_back({ 2, j });

    // Row 3: mirror of row 1
    valid_cells.push_back({ 3, 1 });
    valid_cells.push_back({ 3, 2 });
    valid_cells.push_back({ 3, 3 });

    // Row 4: only center column
    valid_cells.push_back({ 4, 2 });

    // Initialize all cells to spaces
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            board[i][j] = ' ';

    // Mark invalid cells with '.'
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (!is_valid_cell(i, j))
                board[i][j] = '.';
}

/**
 * @brief Check if coordinates are part of the diamond
 * @param x Row index
 * @param y Column index
 * @return true if the cell is valid, false otherwise
 */
bool Diamond_TTT_Board::is_valid_cell(int x, int y) const {
    for (const auto& cell : valid_cells)
        if (cell.first == x && cell.second == y) return true;
    return false;
}

/**
 * @brief Updates the board with a move
 * @param move Pointer to a Move object
 * @return true if move was valid and applied
 */
bool Diamond_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid coordinates! Must be between 0-4.\n";
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
 * @param x Row index
 * @param y Column index
 */
void Diamond_TTT_Board::undo_move(int x, int y) {
    board[x][y] = ' ';
    n_moves--;
}

/**
 * @brief Get all empty cells (for AI)
 * @return vector of coordinates of empty valid cells
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
 * @param x Row
 * @param y Column
 * @return error message or empty string
 */
string Diamond_TTT_Board::validate_move(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return "Coordinates must be 0-4!";
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
 * @param player Pointer to player
 * @return true if player satisfies diamond TTT winning condition
 */
bool Diamond_TTT_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    auto all_lines = get_all_lines();
    vector<vector<pair<int, int>>> completed_3lines;
    vector<vector<pair<int, int>>> completed_4lines;

    // Collect all completed lines for this player
    for (const auto& line : all_lines) {
        bool complete = true;
        for (const auto& cell : line)
            if (board[cell.first][cell.second] != symbol) {
                complete = false;
                break;
            }

        if (complete) {
            if (line.size() == 3) completed_3lines.push_back(line);
            else if (line.size() == 4) completed_4lines.push_back(line);
        }
    }

    // Need at least one 3-line and one 4-line
    if (completed_3lines.empty() || completed_4lines.empty()) return false;

    // Check all combinations of 3-lines and 4-lines
    for (const auto& three_line : completed_3lines) {
        // Determine direction of the 3-line
        string dir3 = "other";
        if (three_line.size() > 1) {
            int dx = three_line[1].first - three_line[0].first;
            int dy = three_line[1].second - three_line[0].second;
            if (dx == 0) dir3 = "horizontal";
            else if (dy == 0) dir3 = "vertical";
            else if (abs(dx) == abs(dy)) dir3 = "diagonal";
        }

        for (const auto& four_line : completed_4lines) {
            // Determine direction of the 4-line
            string dir4 = "other";
            if (four_line.size() > 1) {
                int dx = four_line[1].first - four_line[0].first;
                int dy = four_line[1].second - four_line[0].second;
                if (dx == 0) dir4 = "horizontal";
                else if (dy == 0) dir4 = "vertical";
                else if (abs(dx) == abs(dy)) dir4 = "diagonal";
            }

            // Must be in different directions
            if (dir3 == dir4) continue;

            // Check if they share any cell
            bool shares_cell = false;
            for (const auto& cell3 : three_line) {
                for (const auto& cell4 : four_line) {
                    if (cell3.first == cell4.first && cell3.second == cell4.second) {
                        shares_cell = true;
                        break;
                    }
                }
                if (shares_cell) break;
            }

            // They must NOT share any cell
            if (!shares_cell) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Check if game is draw
 * @param player Pointer to player
 * @return true if board full and no winner
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
 * @param player Pointer to player
 * @return true if game finished
 */
bool Diamond_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Debug helper: print win status
 * @param player Pointer to player
 */
void Diamond_TTT_Board::debug_win_check(Player<char>* player) {
    cout << "\n=== DEBUG for Player " << player->get_symbol() << " ===\n";
    if (is_win(player)) cout << "PLAYER WINS!\n";
    else cout << "Not winning yet.\n";
}

/**
 * @brief Get line cells starting from (start_x,start_y) in direction (dx,dy)
 * @param start_x Row
 * @param start_y Column
 * @param dx Row increment
 * @param dy Column increment
 * @param length Length of line
 * @return vector of coordinates along the line
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
 * @brief Generate all possible winning lines
 * @return vector of lines (each line is vector of coordinates)
 */
vector<vector<pair<int, int>>> Diamond_TTT_Board::get_all_lines() {
    vector<vector<pair<int, int>>> all_lines;

    // HORIZONTAL
    all_lines.push_back(get_line_cells(1, 1, 0, 1, 3));
    all_lines.push_back(get_line_cells(2, 0, 0, 1, 4));
    all_lines.push_back(get_line_cells(2, 1, 0, 1, 4));
    all_lines.push_back(get_line_cells(3, 1, 0, 1, 3));

    // VERTICAL
    all_lines.push_back(get_line_cells(0, 2, 1, 0, 3));
    all_lines.push_back(get_line_cells(1, 2, 1, 0, 3));
    all_lines.push_back(get_line_cells(2, 2, 1, 0, 3));
    all_lines.push_back(get_line_cells(1, 1, 1, 0, 3));
    all_lines.push_back(get_line_cells(1, 3, 1, 0, 3));
    all_lines.push_back(get_line_cells(0, 2, 1, 0, 4));
    all_lines.push_back(get_line_cells(1, 2, 1, 0, 4));

    // DIAGONALS
    all_lines.push_back(get_line_cells(0, 2, 1, -1, 3));
    all_lines.push_back(get_line_cells(1, 1, 1, 1, 3));
    all_lines.push_back(get_line_cells(1, 3, 1, -1, 3));
    all_lines.push_back(get_line_cells(0, 2, 1, 1, 3));
    all_lines.push_back(get_line_cells(2, 0, 1, 1, 3));
    all_lines.push_back(get_line_cells(2, 1, 1, 1, 3));

    // 4-LINE DIAGONALS
    all_lines.push_back(get_line_cells(1, 1, 1, 1, 4));
    all_lines.push_back(get_line_cells(1, 3, 1, -1, 4));

    // Filter valid lines
    vector<vector<pair<int, int>>> valid_lines;
    for (const auto& line : all_lines)
        if (!line.empty()) valid_lines.push_back(line);

    return valid_lines;
}

// ============================================================================
// DIAMOND_TTT_UI IMPLEMENTATION
// ============================================================================

Diamond_TTT_UI::Diamond_TTT_UI() : UI<char>("=== Diamond Tic-Tac-Toe ===", 3) {}

/**
 * @brief Set up two players
 * @return array of two player pointers
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
            board->update_board(new Move<char>(cell.first, cell.second, current_symbol));

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
            board->update_board(new Move<char>(cell.first, cell.second, current_symbol));

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
        // Simple heuristic: prefer center cells first
        vector<pair<int, int>> center_cells = { {0, 2}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 2}, {3, 3}, {4, 2} };

        // Check for winning move
        for (auto cell : empty_cells) {
            board->update_board(new Move<char>(cell.first, cell.second, ai_symbol));
            Player<char> temp_ai("AI", ai_symbol, PlayerType::COMPUTER);
            if (board->is_win(&temp_ai)) {
                board->undo_move(cell.first, cell.second);
                return cell;
            }
            board->undo_move(cell.first, cell.second);
        }

        // Check for blocking opponent's winning move
        for (auto cell : empty_cells) {
            board->update_board(new Move<char>(cell.first, cell.second, opponent_symbol));
            Player<char> temp_opp("OPP", opponent_symbol, PlayerType::COMPUTER);
            if (board->is_win(&temp_opp)) {
                board->undo_move(cell.first, cell.second);
                return cell;
            }
            board->undo_move(cell.first, cell.second);
        }

        // Prefer center cells
        for (auto cell : center_cells) {
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
        board->update_board(new Move<char>(cell.first, cell.second, ai_symbol));
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
void Diamond_TTT_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n=== Diamond Tic-Tac-Toe ===\n";
    UI<char>::display_board_matrix(matrix);
    cout << "Note: '.' marks invalid cells (not part of diamond shape)\n";
}