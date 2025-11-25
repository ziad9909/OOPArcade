#include "Timed_TTT_Classes.h"
#include <iostream>
#include <cstdlib> // For rand()

// --- Timed_TTT_Board Implementation ---

Timed_TTT_Board::Timed_TTT_Board() : Board(3, 3) {
    // Initialize the board with empty cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = emptyCell;
        }
    }
}

bool Timed_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if position is valid and cell is empty
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != emptyCell) {
        cout << "Invalid position. Try again.\n";
        return false;
    }

    // Apply the move
    board[x][y] = symbol;
    moveHistory.push({ x, y });
    n_moves++;

    // Remove oldest move after every 3 moves
    if (n_moves >= 3 && n_moves % 3 == 0) {
        removeOldestMove();
    }

    return true;
}

void Timed_TTT_Board::removeOldestMove() {
    if (!moveHistory.empty()) {
        auto oldestMove = moveHistory.front();
        moveHistory.pop();

        int x = oldestMove.first;
        int y = oldestMove.second;

        cout << "Oldest move at (" << x << ", " << y << ") has been removed!\n";
        board[x][y] = emptyCell;
    }
}

bool Timed_TTT_Board::is_draw(Player<char>* player) {
    // Game is a draw if board is full and no winner
    // But in this game, the board never gets completely full due to move removal
    // So we'll define draw as no winner after a reasonable number of moves
    return (n_moves >= 18 && !is_win(player)); // Arbitrary limit to prevent infinite games
}

bool Timed_TTT_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    return checkThreeInRow(symbol);
}

bool Timed_TTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool Timed_TTT_Board::checkThreeInRow(char symbol) {
    // Check all 8 possible winning lines

    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
    }

    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
            return true;
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;

    return false;
}

// --- Timed_TTT_UI Implementation ---

Timed_TTT_UI::Timed_TTT_UI()
    : UI<char>("Welcome to Timed Tic-Tac-Toe! (Oldest moves disappear every 3 moves)", 3) {}

Player<char>* Timed_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Player<char>** Timed_TTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // Set up Player X
    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    // Set up Player O
    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Move<char>* Timed_TTT_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol()
            << "), enter your move (row and column, 0-2): ";
        cin >> x >> y;
    }
    else { // COMPUTER player (Random)
        cout << "Computer player " << player->get_name() << " is thinking..." << endl;

        // Get the board to check for empty cells
        Timed_TTT_Board* board = dynamic_cast<Timed_TTT_Board*>(player->get_board_ptr());
        auto boardMatrix = board->get_board_matrix();

        // Find all empty cells
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (boardMatrix[i][j] == '.') {
                    emptyCells.push_back({ i, j });
                }
            }
        }

        // Pick a random empty cell
        if (!emptyCells.empty()) {
            int randomIndex = rand() % emptyCells.size();
            x = emptyCells[randomIndex].first;
            y = emptyCells[randomIndex].second;
        }
        else {
            x = y = 0; // Fallback (shouldn't happen in normal gameplay)
        }

        cout << "Computer chose position (" << x << ", " << y << ")" << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}