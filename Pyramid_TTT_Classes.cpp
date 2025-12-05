#include "Pyramid_TTT_Classes.h"

// =============================
//  Constructor: create pyramid
// =============================
Pyramid_TTT_Board::Pyramid_TTT_Board() : Board(3, 5)
{
    // Initialize all cells as '#'
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            board[i][j] = '#';

    // Valid pyramid cells:
    board[2][0] = board[2][1] = board[2][2] = board[2][3] = board[2][4] = '_';
    board[1][1] = board[1][2] = board[1][3] = '_';
    board[0][2] = '_';
}

// =============================
//  Update board
// =============================
bool Pyramid_TTT_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    // Out of range
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    // Invalid pyramid cell
    if (board[x][y] == '#')
        return false;

    // Occupied
    if (board[x][y] != '_')
        return false;

    board[x][y] = sym;
    n_moves++;

    return true;
}

// =============================
//  Draw check
// =============================
bool Pyramid_TTT_Board::is_draw(Player<char>* player)
{
    return n_moves == 9;  // total valid cells = 9
}

// =============================
//  Win checking
// =============================
bool Pyramid_TTT_Board::is_win(Player<char>* player)
{
    char s = player->get_symbol();

    // Check all 3-in-a-row manually

    // Row 0 (5 cells)
    for (int i = 0; i <= 2; i++)
        if (board[2][i] == s && board[2][i + 1] == s && board[2][i + 2] == s)
            return true;

    // Row 1 (3 cells)
    if (board[1][1] == s && board[1][2] == s && board[1][3] == s)
        return true;

    // Vertical
    if (board[0][2] == s && board[1][2] == s && board[2][2] == s)
        return true;

    // Diagonals
    if (board[0][2] == s && board[1][1] == s && board[2][0] == s)
        return true;

    if (board[0][2] == s && board[1][3] == s && board[2][4] == s)
        return true;

    return false;
}

// =============================
// Game over
// =============================
bool Pyramid_TTT_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}

// =============================
// UI: getting a move
// =============================
Move<char>* Pyramid_TTT_UI::get_move(Player<char>* player)
{
    if (player->get_type() == PlayerType::COMPUTER) {
        RandomComputerPlayer* bot = dynamic_cast<RandomComputerPlayer*>(player);
        cout << player->get_name() << " (Computer) is playing...\n";
        return bot->get_computer_move();
    }
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ") enter row & column: ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}


Player<char>* Pyramid_TTT_UI::create_player(string& name, char symbol, PlayerType type)
{
    if (type == PlayerType::COMPUTER)
        return new RandomComputerPlayer(name, symbol);

    return new Player<char>(name, symbol, PlayerType::HUMAN);
}