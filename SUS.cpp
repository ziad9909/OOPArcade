#include "SUS.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

SUS_board::SUS_board() : Board<char>(3, 3) {
    srand(static_cast<unsigned int>(time(0)));
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool SUS_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == blank_symbol) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    return false;
}

int SUS_board::get_score(Player<char>* player) {
    int score = 0;
    char player_symbol = player->get_symbol();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {

            if (i + 2 < rows && board[i][j]=='S' && board[i+1][j]=='U' && board[i+2][j]=='S') {
                if (player_symbol == 'S') {
                    score += 2;
                } else if (player_symbol == 'U') {
                    score++;
                }
            }

            if (j + 2 < columns && board[i][j]=='S' && board[i][j+1]=='U' && board[i][j+2]=='S') {
                if (player_symbol == 'S') {
                    score += 2;
                } else if (player_symbol == 'U') {
                    score++;
                }
            }

            if (i + 2 < rows && j + 2 < columns && board[i][j]=='S' && board[i+1][j+1]=='U' && board[i+2][j+2]=='S') {
                if (player_symbol == 'S') {
                    score += 2;
                } else if (player_symbol == 'U') {
                    score++;
                }
            }

            if (i + 2 < rows && j - 2 >= 0 && board[i][j]=='S' && board[i+1][j-1]=='U' && board[i+2][j-2]=='S') {
                if (player_symbol == 'S') {
                    score += 2;
                } else if (player_symbol == 'U') {
                    score++;
                }
            }
        }
    }
    return score;
}

bool SUS_board::is_win(Player<char>* player) {
    if (n_moves < 9) return false;

    char other_symbol = (player->get_symbol() == 'S') ? 'U' : 'S';
    Player<char> temp_other("temp", other_symbol, PlayerType::HUMAN);

    int player_score = get_score(player);
    int other_score = get_score(&temp_other);

    return player_score > other_score;
}

bool SUS_board::is_lose(Player<char>* player) {
    if (n_moves < 9) return false;
    char other_symbol = (player->get_symbol() == 'S') ? 'U' : 'S';
    Player<char> temp_other("temp", other_symbol, PlayerType::HUMAN);

    int player_score = get_score(player);
    int other_score = get_score(&temp_other);
    return player_score < other_score;
}

bool SUS_board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;
    char other_symbol = (player->get_symbol() == 'S') ? 'U' : 'S';
    Player<char> temp_other("temp", other_symbol, PlayerType::HUMAN);
    int player_score = get_score(player);
    int other_score = get_score(&temp_other);
    return player_score == other_score;
}

bool SUS_board::game_is_over(Player<char>* player) {
    return n_moves == 9;
}

SUS_player::SUS_player() : UI<char>("Welcome to SUS Game", 3) {
    srand(static_cast<unsigned int>(time(0)));
}

SUS_player::~SUS_player() {}

Player<char>* SUS_player::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** SUS_player::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'S', type1);

    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'U', type2);

    return players;
}

Move<char>* SUS_player::get_move(Player<char>* player) {
    int x, y;
    Board<char>* board = player->get_board_ptr();
    char symbol = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << symbol << "), enter your move (row col): ";
        do {
            cin >> x >> y;

            if (x < 0 || x >= board->get_rows() || y < 0 || y >= board->get_columns()) {
                cout << "Invalid position! Enter row and col (0-2): ";
                continue;
            }
            if (board->get_cell(x, y) != '.') {
                cout << "Cell already occupied! Enter another position (row col): ";
                continue;
            }
            break;
        } while (true);

        cout << player->get_name() << " placed '" << symbol << "' at (" << x << ", " << y << ")" << endl;

    } else {
        cout << "\nComputer player " << player->get_name() << " (" << symbol << ") is thinking..." << endl;

        do {
            x = rand() % board->get_rows();
            y = rand() % board->get_columns();
        } while (board->get_cell(x, y) != '.');

        cout << "Computer " << player->get_name() << " placed '" << symbol << "' at (" << x << ", " << y << ")" << endl;
    }
    return new Move<char>(x, y, player->get_symbol());
}