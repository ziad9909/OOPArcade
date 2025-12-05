/**
 * base.js
 * Core JavaScript ES6 classes that mirror the C++ BoardGame_Classes.h structure
 * These classes provide the foundation for all board game implementations
 */

// ============================================
// PLAYER TYPES ENUM
// ============================================

/**
 * PlayerType - Enum for different player types
 * Mirrors the C++ PlayerType enum
 */
const PlayerType = {
    HUMAN: 'HUMAN',
    RANDOM: 'RANDOM',
    AI: 'AI',
    COMPUTER: 'COMPUTER'
};

// ============================================
// MOVE CLASS
// ============================================

/**
 * Move - Represents a single move in a board game
 * @template T - Type of symbol placed on the board (e.g., char, int)
 * 
 * Mirrors the C++ Move<T> class
 */
class Move {
    /**
     * @param {number} x - Row index
     * @param {number} y - Column index
     * @param {*} symbol - Symbol used in the move
     */
    constructor(x, y, symbol) {
        this.x = x;
        this.y = y;
        this.symbol = symbol;
    }

    /** Get row index */
    getX() { return this.x; }

    /** Get column index */
    getY() { return this.y; }

    /** Get the move symbol */
    getSymbol() { return this.symbol; }
}

// ============================================
// BOARD CLASS
// ============================================

/**
 * Board - Base class for any board used in board games
 * @template T - Type of elements stored on the board
 * 
 * Mirrors the C++ Board<T> class
 */
class Board {
    /**
     * @param {number} rows - Number of rows
     * @param {number} columns - Number of columns
     */
    constructor(rows, columns) {
        this.rows = rows;
        this.columns = columns;
        this.nMoves = 0;
        
        // Initialize 2D board array
        this.board = Array(rows).fill(null).map(() => Array(columns).fill(null));
    }

    /**
     * Update the board with a new move
     * @param {Move} move - The move object containing position and symbol
     * @returns {boolean} - true if move is valid and applied, false otherwise
     */
    updateBoard(move) {
        throw new Error('updateBoard() must be implemented by subclass');
    }

    /**
     * Check if a player has won
     * @param {Player} player - The player to check
     * @returns {boolean}
     */
    isWin(player) {
        throw new Error('isWin() must be implemented by subclass');
    }

    /**
     * Check if a player has lost
     * @param {Player} player - The player to check
     * @returns {boolean}
     */
    isLose(player) {
        return false; // Default implementation
    }

    /**
     * Check if the game ended in a draw
     * @param {Player} player - The player to check
     * @returns {boolean}
     */
    isDraw(player) {
        throw new Error('isDraw() must be implemented by subclass');
    }

    /**
     * Check if the game is over
     * @param {Player} player - The player to check
     * @returns {boolean}
     */
    gameIsOver(player) {
        return this.isWin(player) || this.isLose(player) || this.isDraw(player);
    }

    /** Get a copy of the board matrix */
    getBoardMatrix() {
        return this.board.map(row => [...row]);
    }

    /** Get number of rows */
    getRows() { return this.rows; }

    /** Get number of columns */
    getColumns() { return this.columns; }

    /** Get cell value at position (x, y) */
    getCell(x, y) {
        if (x >= 0 && x < this.rows && y >= 0 && y < this.columns) {
            return this.board[x][y];
        }
        return null;
    }

    /** Get number of moves made */
    getMoveCount() { return this.nMoves; }
}

// ============================================
// PLAYER CLASS
// ============================================

/**
 * Player - Base class for all players (human or AI)
 * @template T - Type of symbol used by the player
 * 
 * Mirrors the C++ Player<T> class
 */
class Player {
    /**
     * @param {string} name - Player name
     * @param {*} symbol - Player's symbol on board
     * @param {string} type - Player type (from PlayerType enum)
     */
    constructor(name, symbol, type) {
        this.name = name;
        this.symbol = symbol;
        this.type = type;
        this.boardPtr = null;
    }

    /** Get the player's name */
    getName() { return this.name; }

    /** Get player type */
    getType() { return this.type; }

    /** Get the player's symbol */
    getSymbol() { return this.symbol; }

    /** Get a pointer to the game board */
    getBoardPtr() { return this.boardPtr; }

    /** Assign the board pointer for the player */
    setBoardPtr(board) { this.boardPtr = board; }

    /**
     * Get a move from this player (to be called by UI)
     * For AI players, this should compute the move
     * For human players, this is handled by UI
     * @returns {Move}
     */
    getMove() {
        // This will be handled differently based on player type
        return null;
    }
}

// ============================================
// RANDOM AI PLAYER
// ============================================

/**
 * RandomAIPlayer - AI player that makes random moves
 */
class RandomAIPlayer extends Player {
    constructor(name, symbol) {
        super(name, symbol, PlayerType.RANDOM);
    }

    /**
     * Get a random valid move
     * @returns {Move}
     */
    getMove() {
        if (!this.boardPtr) return null;

        const board = this.boardPtr;
        const emptyCells = [];

        // Find all empty cells
        for (let i = 0; i < board.getRows(); i++) {
            for (let j = 0; j < board.getColumns(); j++) {
                if (board.getCell(i, j) === null || board.getCell(i, j) === '.' || board.getCell(i, j) === 0) {
                    emptyCells.push([i, j]);
                }
            }
        }

        // Pick a random empty cell
        if (emptyCells.length > 0) {
            const [x, y] = emptyCells[Math.floor(Math.random() * emptyCells.length)];
            return new Move(x, y, this.symbol);
        }

        return null;
    }
}

// ============================================
// GAME MANAGER CLASS
// ============================================

/**
 * GameManager - Controls the flow of a board game between two players
 * 
 * Mirrors the C++ GameManager<T> class
 */
class GameManager {
    /**
     * @param {Board} board - Game board
     * @param {Player[]} players - Array of two players
     * @param {UI} ui - User interface controller
     */
    constructor(board, players, ui) {
        this.board = board;
        this.players = players;
        this.ui = ui;
        this.currentPlayerIndex = 0;
        this.gameOver = false;

        // Set board pointers for both players
        this.players[0].setBoardPtr(board);
        this.players[1].setBoardPtr(board);
    }

    /**
     * Get the current player
     * @returns {Player}
     */
    getCurrentPlayer() {
        return this.players[this.currentPlayerIndex];
    }

    /**
     * Get the opponent player
     * @returns {Player}
     */
    getOpponentPlayer() {
        return this.players[1 - this.currentPlayerIndex];
    }

    /**
     * Switch to the next player
     */
    switchPlayer() {
        this.currentPlayerIndex = 1 - this.currentPlayerIndex;
        this.ui.updateTurnIndicator(this.getCurrentPlayer());
    }

    /**
     * Process a move attempt
     * @param {Move} move - The move to process
     * @returns {boolean} - true if move was valid and processed
     */
    processMove(move) {
        if (this.gameOver) return false;

        const currentPlayer = this.getCurrentPlayer();

        // Try to update the board
        if (this.board.updateBoard(move)) {
            // Update UI
            this.ui.displayBoard(this.board);

            // Check win condition
            if (this.board.isWin(currentPlayer)) {
                this.gameOver = true;
                this.ui.displayMessage(`${currentPlayer.getName()} wins!`, 'win');
                return true;
            }

            // Check lose condition
            if (this.board.isLose(currentPlayer)) {
                this.gameOver = true;
                const opponent = this.getOpponentPlayer();
                this.ui.displayMessage(`${opponent.getName()} wins!`, 'win');
                return true;
            }

            // Check draw condition
            if (this.board.isDraw(currentPlayer)) {
                this.gameOver = true;
                this.ui.displayMessage('It\'s a draw!', 'draw');
                return true;
            }

            // Switch to next player
            this.switchPlayer();

            // If next player is AI, trigger their move
            const nextPlayer = this.getCurrentPlayer();
            if (nextPlayer.getType() === PlayerType.RANDOM || 
                nextPlayer.getType() === PlayerType.AI || 
                nextPlayer.getType() === PlayerType.COMPUTER) {
                setTimeout(() => this.makeAIMove(), 500);
            }

            return true;
        }

        return false;
    }

    /**
     * Make a move for AI player
     */
    makeAIMove() {
        if (this.gameOver) return;

        const currentPlayer = this.getCurrentPlayer();
        const move = currentPlayer.getMove();

        if (move) {
            this.processMove(move);
        }
    }

    /**
     * Check if game is over
     * @returns {boolean}
     */
    isGameOver() {
        return this.gameOver;
    }

    /**
     * Restart the game
     */
    restart() {
        this.currentPlayerIndex = 0;
        this.gameOver = false;
        // Board will be recreated by UI
    }
}

// ============================================
// UI BASE CLASS
// ============================================

/**
 * UI - Base class for handling user interface and input/output
 * 
 * Mirrors the C++ UI<T> class
 * This is a simplified version that works with DOM
 */
class UI {
    constructor() {
        this.boardContainer = document.getElementById('board-container');
        this.messageContainer = document.getElementById('game-message');
        this.turnIndicator = document.getElementById('turn-indicator');
        this.currentPlayerSpan = document.getElementById('current-player');
        this.additionalInfo = document.getElementById('additional-info');
    }

    /**
     * Display the board in the DOM
     * @param {Board} board
     */
    displayBoard(board) {
        throw new Error('displayBoard() must be implemented by subclass');
    }

    /**
     * Display a message to the user
     * @param {string} message - The message to display
     * @param {string} type - Message type: 'win', 'lose', 'draw', 'info'
     */
    displayMessage(message, type = 'info') {
        this.messageContainer.textContent = message;
        this.messageContainer.className = `game-message ${type}`;
    }

    /**
     * Clear the message
     */
    clearMessage() {
        this.messageContainer.textContent = '';
        this.messageContainer.className = 'game-message';
    }

    /**
     * Update turn indicator
     * @param {Player} player
     */
    updateTurnIndicator(player) {
        if (this.currentPlayerSpan) {
            this.currentPlayerSpan.textContent = player.getName();
        }
    }

    /**
     * Create a cell element for the board
     * @param {number} row
     * @param {number} col
     * @param {*} value
     * @param {Function} onClick
     * @returns {HTMLElement}
     */
    createCell(row, col, value, onClick) {
        const cell = document.createElement('div');
        cell.className = 'cell';
        cell.dataset.row = row;
        cell.dataset.col = col;

        if (value !== null && value !== '.' && value !== 0) {
            cell.textContent = value;
            cell.classList.add('occupied');
        }

        if (onClick) {
            cell.addEventListener('click', () => onClick(row, col));
        }

        return cell;
    }

    /**
     * Highlight winning cells
     * @param {number[][]} winningCells - Array of [row, col] coordinates
     */
    highlightWinningCells(winningCells) {
        winningCells.forEach(([row, col]) => {
            const cell = document.querySelector(`[data-row="${row}"][data-col="${col}"]`);
            if (cell) {
                cell.classList.add('winning');
            }
        });
    }

    /**
     * Clear all highlights
     */
    clearHighlights() {
        document.querySelectorAll('.cell.winning').forEach(cell => {
            cell.classList.remove('winning');
        });
    }
}

// ============================================
// UTILITY FUNCTIONS
// ============================================

/**
 * Utility function to get URL parameters
 * @param {string} param - Parameter name
 * @returns {string|null}
 */
function getURLParameter(param) {
    const urlParams = new URLSearchParams(window.location.search);
    return urlParams.get(param);
}

/**
 * Utility function to shuffle an array (Fisher-Yates algorithm)
 * @param {Array} array
 * @returns {Array}
 */
function shuffleArray(array) {
    const newArray = [...array];
    for (let i = newArray.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [newArray[i], newArray[j]] = [newArray[j], newArray[i]];
    }
    return newArray;
}

/**
 * Utility function to deep copy a 2D array
 * @param {Array<Array>} array
 * @returns {Array<Array>}
 */
function deepCopy2DArray(array) {
    return array.map(row => [...row]);
}

// Export for use in other files (if using modules)
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        PlayerType,
        Move,
        Board,
        Player,
        RandomAIPlayer,
        GameManager,
        UI,
        getURLParameter,
        shuffleArray,
        deepCopy2DArray
    };
}

