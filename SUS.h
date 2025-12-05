#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class SUS_board
 * @brief Class representing the SUS Tic-Tac-Toe board.
 *
 * Handles board state, moves, score calculation, win/draw checking,
 * and AI logic using minimax with alpha-beta pruning.
 */
class SUS_board : public Board<char> {
public:
    /** @brief Constructor initializes an empty 3x3 board and scores. */
    SUS_board();

    /**
     * @brief Updates the board with a move.
     * @param move Pointer to Move object containing row, column, and symbol.
     * @return true if move is valid and placed, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won.
     * @param player Pointer to the Player object.
     * @return true if player has more points than the opponent, false otherwise.
     */
    bool is_win(Player<char>* player);

    /** @brief Checks if the given player has lost. */
    bool is_lose(Player<char>* player);

    /** @brief Checks if the game ended in a draw. */
    bool is_draw(Player<char>* player);

    /** @brief Checks if the game board is full. */
    bool game_is_over(Player<char>* player);

    /** @brief Returns the current score of the given player. */
    int get_score(Player<char>* player);

    /**
     * @brief Checks how many new SUS sequences were completed by the last move.
     * @param x Row index of the last move.
     * @param y Column index of the last move.
     * @return Number of new SUS sequences completed.
     */
    int check_new_sequences(int x, int y);

    // ===================== AI FUNCTIONS =====================
    /** @brief Returns a vector of empty cells on the board. */
    vector<pair<int,int>> get_empty_cells();

    /** @brief Evaluates the board state from AI perspective. */
    int evaluate_state(char aiSymbol);

    /**
     * @brief Minimax algorithm with alpha-beta pruning.
     * @param depth Current depth of recursion.
     * @param maximizing True if AI's turn, false if human's turn.
     * @param aiSymbol Symbol of the AI player ('S' or 'U').
     * @param humanSymbol Symbol of the human player.
     * @param alpha Alpha value for pruning.
     * @param beta Beta value for pruning.
     * @return Evaluated score for the current board state.
     */
    int minimax(int depth,bool maximizing,char aiSymbol,char humanSymbol,int alpha,int beta);

    /**
     * @brief Finds the best move for AI using minimax.
     * @param aiSymbol AI player's symbol.
     * @param humanSymbol Human player's symbol.
     * @return Pair<int,int> representing the row and column of best move.
     */
    pair<int,int> get_best_move(char aiSymbol,char humanSymbol);

private:
    char blank_symbol = '.';   /**< Symbol for empty cell */
    int score_S = 0;           /**< Accumulated score for player S */
    int score_U = 0;           /**< Accumulated score for player U */
};

/**
 * @class SUS_player
 * @brief Handles player setup and moves (Human or AI) for SUS game.
 */
class SUS_player : public UI<char> {
public:
    /** @brief Constructor initializes the UI. */
    SUS_player();

    /** @brief Destructor */
    ~SUS_player();

    /**
     * @brief Creates a new player.
     * @param name Name of the player.
     * @param symbol Player's symbol ('S' or 'U').
     * @param type Player type (Human or Computer).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name,char symbol,PlayerType type) override;

    /**
     * @brief Sets up two players (name, symbol, type).
     * @return Array of pointers to Player objects.
     */
    Player<char>** setup_players() override;

    /**
     * @brief Gets the next move from a player (Human input or AI).
     * @param player Pointer to the Player object making the move.
     * @return Pointer to a Move object representing the chosen move.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif
