#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class Four_in_a_row_board
 * @brief Represents the game board for the Four-in-a-Row (Connect 4) game.
 *
 * Handles board updates, win/draw checking, and AI functions.
 */
class Four_in_a_row_board: public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol for empty cells

public:
    /**
     * @brief Constructor: Initializes a 6x7 board and sets all cells to blank.
     */
    Four_in_a_row_board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the Move object containing row/column and symbol.
     * @return true if the move was successful, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player.
     * @return true if the player won, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * Always returns false (not used in this game).
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game ended in a draw.
     * @param player Pointer to the player (not used in draw check).
     * @return true if the board is full and no one won.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if the game is over (win or draw).
     * @param player Pointer to the player (not used in check).
     * @return true if game is over.
     */
    bool game_is_over(Player<char>* player);

    // ---------------- AI FUNCTIONS ----------------

    /**
     * @brief Returns all valid columns where a move can be made.
     * @return Vector of column indices.
     */
    vector<int> get_valid_columns();

    /**
     * @brief Evaluates the board for the AI.
     * @param aiSymbol Symbol of AI player ('X' or 'O').
     * @return Numeric score of the board from AI's perspective.
     */
    int evaluate_board(char aiSymbol);

    /**
     * @brief Counts sequences of a given length for a symbol.
     * @param symbol Player's symbol ('X' or 'O').
     * @param length Length of sequence to check.
     * @return Number of sequences of given length.
     */
    int count_sequences(char symbol, int length);

    /**
     * @brief Minimax algorithm with alpha-beta pruning.
     * @param depth Remaining depth to search.
     * @param maximizing True if AI is maximizing, false if minimizing.
     * @param aiSymbol AI player's symbol.
     * @param humanSymbol Human player's symbol.
     * @param alpha Alpha value for pruning.
     * @param beta Beta value for pruning.
     * @return Evaluated score for this board state.
     */
    int minimax(int depth, bool maximizing, char aiSymbol, char humanSymbol, int alpha, int beta);

    /**
     * @brief Returns the best move column for AI.
     * @param aiSymbol AI player's symbol.
     * @param humanSymbol Human player's symbol.
     * @return Column index of best move.
     */
    int get_best_move(char aiSymbol, char humanSymbol);

    /**
     * @brief Checks if a symbol has a winning sequence on the board.
     * @param symbol Player's symbol.
     * @return true if symbol has 4 in a row.
     */
    bool check_win_for_symbol(char symbol);

    /**
     * @brief Undoes the last move in a column.
     * @param col Column index to undo.
     */
    void undo_move(int col);
};

/**
 * @class Four_in_a_row_Ui
 * @brief User interface for the Four-in-a-Row game.
 *
 * Handles player setup and move input.
 */
class Four_in_a_row_Ui: public UI<char> {
public:
    Four_in_a_row_Ui();
    ~Four_in_a_row_Ui();

    /**
     * @brief Creates a player object.
     * @param name Player's name.
     * @param symbol Player's symbol.
     * @param type Player type (Human or Computer).
     * @return Pointer to the created player.
     */
    Player<char>* create_player(string &name, char symbol, PlayerType type);

    /**
     * @brief Sets up two players for the game.
     * @return Array of two player pointers.
     */
    Player<char>** setup_players() override;

    /**
     * @brief Gets a move from a player (human input or AI).
     * @param player Pointer to the player making the move.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif //FOUR_IN_A_ROW_H
