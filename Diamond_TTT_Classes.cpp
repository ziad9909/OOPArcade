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
 * CONSTRUCTOR: Diamond_TTT_Board::Diamond_TTT_Board()
 * PURPOSE: Initialize the 5x5 diamond-shaped board
 * HOW IT WORKS:
 * 1. Calls parent Board<char> constructor with dimensions 5x5
 * 2. Defines which cells are part of the diamond shape
 * 3. Initializes all cells to spaces
 * 4. Marks invalid cells with '.' for visual clarity
 */
Diamond_TTT_Board::Diamond_TTT_Board() : Board<char>(5, 5) {
    // Define diamond shape coordinates (forming a diamond pattern)
    valid_cells.clear();

    // Row 0: only center column
    valid_cells.push_back({ 0, 2 });  // Top point of diamond

    // Row 1: three middle columns  
    valid_cells.push_back({ 1, 1 });  // Left-middle
    valid_cells.push_back({ 1, 2 });  // Center
    valid_cells.push_back({ 1, 3 });  // Right-middle

    // Row 2: all five columns (widest part of diamond)
    for (int j = 0; j < 5; j++) {
        valid_cells.push_back({ 2, j });
    }

    // Row 3: three middle columns (mirror of row 1)
    valid_cells.push_back({ 3, 1 });
    valid_cells.push_back({ 3, 2 });
    valid_cells.push_back({ 3, 3 });

    // Row 4: only center column (bottom point of diamond)
    valid_cells.push_back({ 4, 2 });

    // Initialize all cells to spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }

    // Mark non-diamond cells with '.' to show they're invalid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!is_valid_cell(i, j)) {
                board[i][j] = '.';
            }
        }
    }
}

/**
 * METHOD: Diamond_TTT_Board::is_valid_cell()
 * PURPOSE: Check if coordinates are within the diamond shape
 * HOW IT WORKS: Compares against pre-defined valid_cells list
 */
bool Diamond_TTT_Board::is_valid_cell(int x, int y) const {
    for (const auto& cell : valid_cells) {
        if (cell.first == x && cell.second == y) {
            return true;
        }
    }
    return false;
}

/**
 * METHOD: Diamond_TTT_Board::update_board()
 * PURPOSE: Process a player's move and update the board
 * HOW IT WORKS:
 * 1. Validates coordinates are within bounds
 * 2. Checks if cell is part of diamond shape
 * 3. Verifies cell is empty
 * 4. Places player's symbol if all checks pass
 */
bool Diamond_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    // Check bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid coordinates! Must be between 0-4.\n";
        return false;
    }

    // Check diamond shape
    if (!is_valid_cell(x, y)) {
        cout << "Cell (" << x << "," << y << ") is not in diamond shape!\n";
        return false;
    }

    // Check if empty
    if (board[x][y] != ' ') {
        cout << "Cell (" << x << "," << y << ") already has '" << board[x][y] << "'!\n";
        return false;
    }

    // Valid move - update board
    board[x][y] = sym;
    n_moves++;
    return true;
}

/**
 * METHOD: Diamond_TTT_Board::get_line_cells()
 * PURPOSE: Generate a list of cells along a straight line
 * HOW IT WORKS:
 * 1. Starts from (start_x, start_y)
 * 2. Moves (dx, dy) each step for 'length' steps
 * 3. Validates each cell is within diamond shape
 */
vector<pair<int, int>> Diamond_TTT_Board::get_line_cells(int start_x, int start_y,
    int dx, int dy, int length) {
    vector<pair<int, int>> line;
    int x = start_x;
    int y = start_y;

    for (int i = 0; i < length; i++) {
        // Check bounds and diamond shape
        if (x >= 0 && x < rows && y >= 0 && y < columns && is_valid_cell(x, y)) {
            line.push_back({ x, y });
        }
        else {
            return {}; // Invalid line
        }
        x += dx;
        y += dy;
    }
    return line;
}

/**
 * METHOD: Diamond_TTT_Board::get_all_lines()
 * PURPOSE: Generate all possible winning lines in the diamond
 * HOW IT WORKS:
 * 1. Defines horizontal, vertical, and diagonal lines
 * 2. Uses get_line_cells() to generate each line
 * 3. Filters out invalid lines (outside diamond)
 *
 * IMPORTANT: These are the lines players can win with
 */
vector<vector<pair<int, int>>> Diamond_TTT_Board::get_all_lines() {
    vector<vector<pair<int, int>>> all_lines;

    // ===== HORIZONTAL LINES =====
    all_lines.push_back(get_line_cells(1, 1, 0, 1, 3));  // Row 1, cols 1-3
    all_lines.push_back(get_line_cells(2, 0, 0, 1, 4));  // Row 2, cols 0-3
    all_lines.push_back(get_line_cells(2, 1, 0, 1, 4));  // Row 2, cols 1-4  
    all_lines.push_back(get_line_cells(3, 1, 0, 1, 3));  // Row 3, cols 1-3

    // ===== VERTICAL LINES =====
    all_lines.push_back(get_line_cells(0, 2, 1, 0, 3));  // Col 2, rows 0-2
    all_lines.push_back(get_line_cells(1, 2, 1, 0, 3));  // Col 2, rows 1-3
    all_lines.push_back(get_line_cells(2, 2, 1, 0, 3));  // Col 2, rows 2-4
    all_lines.push_back(get_line_cells(1, 1, 1, 0, 3));  // Col 1, rows 1-3
    all_lines.push_back(get_line_cells(1, 3, 1, 0, 3));  // Col 3, rows 1-3
    all_lines.push_back(get_line_cells(0, 2, 1, 0, 4));  // Col 2, rows 0-3 (4-line)
    all_lines.push_back(get_line_cells(1, 2, 1, 0, 4));  // Col 2, rows 1-4 (4-line)

    // ===== DIAGONAL LINES =====
    // Main diagonals (NW-SE)
    all_lines.push_back(get_line_cells(0, 2, 1, -1, 3)); // (0,2)-(1,1)-(2,0)
    all_lines.push_back(get_line_cells(1, 1, 1, 1, 3));  // (1,1)-(2,2)-(3,3)
    all_lines.push_back(get_line_cells(1, 3, 1, -1, 3)); // (1,3)-(2,2)-(3,1)

    // Anti-diagonals (NE-SW)  
    all_lines.push_back(get_line_cells(0, 2, 1, 1, 3));  // (0,2)-(1,3)-(2,4)
    all_lines.push_back(get_line_cells(2, 0, 1, 1, 3));  // (2,0)-(3,1)-(4,2)
    all_lines.push_back(get_line_cells(2, 1, 1, 1, 3));  // (2,1)-(3,2)-(4,3)

    // ===== 4-LINE DIAGONALS =====
    all_lines.push_back(get_line_cells(1, 1, 1, 1, 4));  // (1,1)-(2,2)-(3,3)-(4,4)
    all_lines.push_back(get_line_cells(1, 3, 1, -1, 4)); // (1,3)-(2,2)-(3,1)-(4,0)

    // Filter out empty/invalid lines
    vector<vector<pair<int, int>>> valid_lines;
    for (const auto& line : all_lines) {
        if (!line.empty()) {
            valid_lines.push_back(line);
        }
    }

    return valid_lines;
}

/**
 * METHOD: Diamond_TTT_Board::is_win()
 * PURPOSE: Check if a player has won according to diamond TTT rules
 * HOW IT WORKS:
 * 1. Get all lines the player has completed (3-lines and 4-lines)
 * 2. For each 3-line, check each 4-line:
 *    a. Are they in different directions? (horizontal/vertical/diagonal)
 *    b. Do they share at least one common cell?
 * 3. Return true if ANY pair meets both conditions
 *
 * This implements the unique winning condition: 3-line + 4-line in different directions
 */
bool Diamond_TTT_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    auto all_lines = get_all_lines();

    // Separate completed lines by length
    vector<vector<pair<int, int>>> completed_3lines;
    vector<vector<pair<int, int>>> completed_4lines;

    for (const auto& line : all_lines) {
        bool complete = true;
        // Check if all cells in line belong to player
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

    // Need at least one 3-line AND one 4-line to possibly win
    if (completed_3lines.empty() || completed_4lines.empty()) {
        return false;
    }

    // Check all combinations of 3-lines and 4-lines
    for (const auto& three_line : completed_3lines) {
        // Determine direction of 3-line
        string dir3 = "other";
        if (three_line.size() > 1) {
            int dx = three_line[1].first - three_line[0].first;
            int dy = three_line[1].second - three_line[0].second;

            if (dx == 0) dir3 = "horizontal";
            else if (dy == 0) dir3 = "vertical";
            else if (abs(dx) == abs(dy)) dir3 = "diagonal";
        }

        for (const auto& four_line : completed_4lines) {
            // Determine direction of 4-line
            string dir4 = "other";
            if (four_line.size() > 1) {
                int dx = four_line[1].first - four_line[0].first;
                int dy = four_line[1].second - four_line[0].second;

                if (dx == 0) dir4 = "horizontal";
                else if (dy == 0) dir4 = "vertical";
                else if (abs(dx) == abs(dy)) dir4 = "diagonal";
            }

            // Check 1: Lines must be in different directions
            if (dir3 == dir4) {
                continue; // Skip same-direction lines
            }

            // Check 2: Lines must share at least one cell
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

            // If both conditions met, player wins!
            if (shares_cell) {
                return true;
            }
        }
    }

    return false;
}

/**
 * METHOD: Diamond_TTT_Board::is_draw()
 * PURPOSE: Check if game is a draw (no winner, board full)
 */
bool Diamond_TTT_Board::is_draw(Player<char>* player) {
    // Check if any valid cell is still empty
    for (const auto& cell : valid_cells) {
        if (board[cell.first][cell.second] == ' ') {
            return false; // Still has empty cells
        }
    }
    // All cells filled AND no winner = draw
    return !is_win(player);
}

/**
 * METHOD: Diamond_TTT_Board::game_is_over()
 * PURPOSE: Check if game has ended (win or draw)
 */
bool Diamond_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * METHOD: Diamond_TTT_Board::validate_move()
 * PURPOSE: Validate move without actually making it (for UI)
 */
string Diamond_TTT_Board::validate_move(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return "Coordinates must be 0-4!";
    }
    if (!is_valid_cell(x, y)) {
        return "Not a diamond cell!";
    }
    if (board[x][y] != ' ') {
        string msg = "Cell occupied by '";
        msg += board[x][y];
        msg += "'!";
        return msg;
    }
    return "";
}

/**
 * METHOD: Diamond_TTT_Board::get_empty_cells()
 * PURPOSE: Get list of available moves (for computer AI)
 */
vector<pair<int, int>> Diamond_TTT_Board::get_empty_cells() const {
    vector<pair<int, int>> empty;
    for (const auto& cell : valid_cells) {
        if (board[cell.first][cell.second] == ' ') {
            empty.push_back(cell);
        }
    }
    return empty;
}

/**
 * METHOD: Diamond_TTT_Board::debug_win_check()
 * PURPOSE: Debug helper to see what lines a player has
 */
void Diamond_TTT_Board::debug_win_check(Player<char>* player) {
    cout << "\n=== DEBUG for Player " << player->get_symbol() << " ===\n";
    if (is_win(player)) {
        cout << "PLAYER WINS!\n";
    }
    else {
        cout << "Not winning yet.\n";
    }
}

// ============================================================================
// DIAMOND_TTT_UI IMPLEMENTATION  
// ============================================================================

/**
 * CONSTRUCTOR: Diamond_TTT_UI::Diamond_TTT_UI()
 * PURPOSE: Initialize UI with welcome message
 */
Diamond_TTT_UI::Diamond_TTT_UI() : UI<char>("=== Diamond Tic-Tac-Toe ===", 3) {}

/**
 * METHOD: Diamond_TTT_UI::setup_players()
 * PURPOSE: Set up two players (human or computer)
 * HOW IT WORKS:
 * 1. Asks for Player X name and type
 * 2. Asks for Player O name and type
 * 3. Creates Player objects with appropriate symbols
 * 4. Returns array of two players
 */
Player<char>** Diamond_TTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // Player X setup
    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    // Player O setup
    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

/**
 * METHOD: Diamond_TTT_UI::create_player()
 * PURPOSE: Create a Player object with given parameters
 */
Player<char>* Diamond_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * METHOD: Diamond_TTT_UI::get_move()
 * PURPOSE: Get a move from a player (human input or computer AI)
 * HOW IT WORKS:
 * For humans: Validates input step-by-step
 * For computers: Picks random empty cell
 */
Move<char>* Diamond_TTT_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        Diamond_TTT_Board* board = dynamic_cast<Diamond_TTT_Board*>(player->get_board_ptr());
        bool valid_move = false;

        while (!valid_move) {
            cout << "\n" << player->get_name() << " (" << player->get_symbol()
                << "), enter your move (row column): ";

            // Get input
            if (!(cin >> x >> y)) {
                cout << "Invalid input! Enter two numbers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // Validate
            string error = board->validate_move(x, y);
            if (!error.empty()) {
                cout << "Error: " << error << "\n";
                continue;
            }

            valid_move = true;
        }
    }
    else {
        // COMPUTER PLAYER: Random move from empty cells
        Diamond_TTT_Board* board = dynamic_cast<Diamond_TTT_Board*>(player->get_board_ptr());
        if (board) {
            auto empty_cells = board->get_empty_cells();
            if (!empty_cells.empty()) {
                int index = rand() % empty_cells.size();
                x = empty_cells[index].first;
                y = empty_cells[index].second;
                cout << "\n" << player->get_name() << " (" << player->get_symbol()
                    << ") chooses: " << x << " " << y << endl;
            }
            else {
                x = y = -1; // No moves
            }
        }
        else {
            x = rand() % 5;
            y = rand() % 5;
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}

/**
 * METHOD: Diamond_TTT_UI::display_board_matrix()
 * PURPOSE: Display the board with diamond shape explanation
 */
void Diamond_TTT_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n" << string(50, '=') << "\n";
    cout << "DIAMOND TIC-TAC-TOE BOARD\n";
    cout << string(50, '=') << "\n";

    // Call parent method to show the grid
    UI<char>::display_board_matrix(matrix);

    // Explain diamond shape and winning conditions
    cout << "\n" << string(50, '-') << "\n";
    cout << "HOW TO WIN:\n";
    cout << "1. Complete ONE line of 3 marks\n";
    cout << "2. Complete ONE line of 4 marks\n";
    cout << "3. Lines must be DIFFERENT directions (horizontal/vertical/diagonal)\n";
    cout << "4. Lines can SHARE ONE cell\n";
    cout << "\nDiamond cells (others marked with '.'):\n";
    cout << "  Row 0: only column 2\n";
    cout << "  Row 1: columns 1, 2, 3\n";
    cout << "  Row 2: ALL columns 0-4\n";
    cout << "  Row 3: columns 1, 2, 3\n";
    cout << "  Row 4: only column 2\n";
    cout << string(50, '=') << "\n";
}