#include "Numerical_TTT_Classes.h"
#include <iostream>
#include <algorithm> // For std::find

// --- Constructor ---
Numerical_TTT_Board::Numerical_TTT_Board() : Board(3, 3) {
    // Initialize the board with 0 (representing empty)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = 0;
        }
    }

    // Fill the available number lists
    odd_nums = { 1, 3, 5, 7, 9 };  // [cite: 344]
    even_nums = { 2, 4, 6, 8 }; // [cite: 344]
}

// --- Virtual Functions Implementation ---

bool Numerical_TTT_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol(); // The number the player wants to place

    // 1. Check if (x, y) is a valid and empty cell
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
        cout << "Invalid position. Try again.\n";
        return false;
    }

    // 2. Check if the number 'num' is valid and available
    vector<int>* target_list = nullptr;

    if (num % 2 != 0) { // It's an odd number
        target_list = &odd_nums;
    }
    else { // It's an even number
        target_list = &even_nums;
    }

    auto it = std::find(target_list->begin(), target_list->end(), num);

    if (it == target_list->end()) {
        // Number not found in the available list [cite: 345]
        cout << "Number " << num << " is not available or invalid. Try again.\n";
        return false;
    }

    // 3. All checks passed. Apply the move.
    board[x][y] = num;
    target_list->erase(it); // Remove the number from the available list [cite: 345]
    n_moves++;
    return true;
}

bool Numerical_TTT_Board::is_draw(Player<int>* player) {
    // Game is a draw if 9 moves have been made and there is no winner [cite: 346]
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_TTT_Board::is_win(Player<int>* player) {
    // Just check the helper function
    return check_win();
}

bool Numerical_TTT_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

// --- Helper Functions Implementation ---

vector<int> Numerical_TTT_Board::get_available_moves(int player_symbol) {
    if (player_symbol == 1) { // 1 is our symbol for the "Odd" player
        return odd_nums;
    }
    else { // 2 is our symbol for the "Even" player
        return even_nums;
    }
}

bool Numerical_TTT_Board::check_win() {
    // Check all 8 lines to see if they sum to 15 [cite: 346]

    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0 &&
            (board[i][0] + board[i][1] + board[i][2] == 15))
            return true;
    }

    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0 &&
            (board[0][j] + board[1][j] + board[2][j] == 15))
            return true;
    }

    // Check diagonals
    if (board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0 &&
        (board[0][0] + board[1][1] + board[2][2] == 15))
        return true;

    if (board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0 &&
        (board[0][2] + board[1][1] + board[2][0] == 15))
        return true;

    return false; // No win found
}

// ... (keep the Numerical_TTT_Board implementation above)

// --- Numerical_TTT_UI Implementation ---

Numerical_TTT_UI::Numerical_TTT_UI()
    : UI<int>("Welcome to Numerical Tic-Tac-Toe!", 3) {} // 3 is cell width

Player<int>* Numerical_TTT_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << (symbol == 1 ? "Odd" : "Even") << ")\n";

    return new Player<int>(name, symbol, type);
}

// THIS IS THE MOST IMPORTANT UI FUNCTION TO OVERRIDE
Player<int>** Numerical_TTT_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // Set up Player 1 (ODD)
    string name1 = get_player_name("Player 1 (Odd)");
    PlayerType type1 = get_player_type_choice("Player 1 (Odd)", type_options);
    players[0] = create_player(name1, 1, type1); // Assign symbol 1 for Odd [cite: 344]

    // Set up Player 2 (EVEN)
    string name2 = get_player_name("Player 2 (Even)");
    PlayerType type2 = get_player_type_choice("Player 2 (Even)", type_options);
    players[1] = create_player(name2, 2, type2); // Assign symbol 2 for Even [cite: 344]

    return players;
}

Move<int>* Numerical_TTT_UI::get_move(Player<int>* player) {
    int x, y, num;
    int player_symbol = player->get_symbol(); // 1 for Odd, 2 for Even

    // Get the board to check available moves
    Numerical_TTT_Board* board = dynamic_cast<Numerical_TTT_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        // Show available numbers
        cout << player->get_name() << " (" << (player_symbol == 1 ? "Odd" : "Even")
            << "), your turn." << endl;
        cout << "Available numbers: ";
        vector<int> available = board->get_available_moves(player_symbol);
        for (int n : available) {
            cout << n << " ";
        }
        cout << endl;

        cout << "Enter your move (row, col, number): ";
        cin >> x >> y >> num;
    }
    else { // COMPUTER player (Random)
        cout << "Computer player " << player->get_name() << " is thinking..." << endl;

        // Pick a random available number
        vector<int> available_nums = board->get_available_moves(player_symbol);
        num = available_nums[rand() % available_nums.size()];

        // Pick a random empty cell
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_board_matrix()[x][y] != 0); // Keep trying until an empty cell is found

        cout << "Computer chose number " << num << " at (" << x << ", " << y << ")" << endl;
    }

    return new Move<int>(x, y, num);
}