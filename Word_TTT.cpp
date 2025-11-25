#include "Word_TTT.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time

Word_TTT_Board::Word_TTT_Board() : Board<char>(3, 3) {
    srand((unsigned int)time(nullptr)); // initialize random seed
    load_dictionary("dic.txt");
    last_x = last_y = -1;

    // Initialize board with spaces
    for (auto& row : board)
        fill(row.begin(), row.end(), ' ');

    n_moves = 0;
}

void Word_TTT_Board::load_dictionary(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error: dic.txt not found!\n";
        return;
    }

    std::string word;
    while (fin >> word) {
        if (word.size() == 3) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            dictionary.insert(word);
        }
    }
}

bool Word_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ')
        return false;

    board[x][y] = symbol;
    last_x = x;
    last_y = y;
    n_moves++;
    return true;
}

bool Word_TTT_Board::is_win(Player<char>* player) {
    return check_win();
}

bool Word_TTT_Board::is_lose(Player<char>* player) {
    return false;
}

bool Word_TTT_Board::is_draw(Player<char>* player) {
    return n_moves == 9 && !check_win();
}

bool Word_TTT_Board::game_is_over(Player<char>* player) {
    return check_win() || is_draw(player);
}

bool Word_TTT_Board::check_win() {
    std::vector<std::string> lines;

    // Check all rows
    for (int i = 0; i < 3; i++) {
        std::string row = "";
        for (int j = 0; j < 3; j++)
            row += board[i][j];
        lines.push_back(row);
    }

    // Check all columns
    for (int j = 0; j < 3; j++) {
        std::string col = "";
        for (int i = 0; i < 3; i++)
            col += board[i][j];
        lines.push_back(col);
    }

    // Main diagonal
    std::string d1 = "";
    for (int i = 0; i < 3; i++)
        d1 += board[i][i];
    lines.push_back(d1);

    // Anti-diagonal
    std::string d2 = "";
    for (int i = 0; i < 3; i++)
        d2 += board[i][2 - i];
    lines.push_back(d2);

    // Check dictionary
    for (std::string line : lines) {
        if (line.find(' ') != std::string::npos) continue;
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);
        if (dictionary.count(line))
            return true;
    }

    return false;
}

// ==================== UI ======================

Word_TTT_UI::Word_TTT_UI() : UI(3) {}

Move<char>* Word_TTT_UI::get_move(Player<char>* player)
{
    Board<char>* board = player->get_board_ptr(); // important

    if (player->get_type() == PlayerType::COMPUTER)
    {
        int x, y;
        char letter;

        // Random empty cell
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_cell(x, y) != ' ');

        // Random letter
        letter = 'A' + (rand() % 26);

        std::cout << "Computer chooses: (" << x << ", " << y << ") letter " << letter << std::endl;
        return new Move<char>(x, y, letter);
    }

    // HUMAN MOVE
    int x, y;
    char letter;
    while (true) {
        std::cout << player->get_name()
            << "'s turn. Enter row(0-2) column(0-2) letter(A-Z): ";
        std::cin >> x >> y >> letter;
        letter = toupper(letter);

        if (x >= 0 && x < 3 && y >= 0 && y < 3 && isalpha(letter) && board->get_cell(x, y) == ' ')
            break;

        std::cout << "Invalid input!\n";
    }

    return new Move<char>(x, y, letter);
}

Player<char>* Word_TTT_UI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, toupper(symbol), type);
}
