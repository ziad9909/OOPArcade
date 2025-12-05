/**
 * tictactoe.js
 * Classic 3x3 Tic Tac Toe game
 * Converted from C++ XO_Classes.cpp
 */

// ============================================
// TIC TAC TOE BOARD CLASS
// ============================================

class TicTacToeBoard extends Board {
    constructor() {
        super(3, 3);
        this.blankSymbol = '.';
        
        // Initialize board with blank symbols
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blankSymbol;
            }
        }
    }

    /**
     * Update the board with a move
     * @param {Move} move
     * @returns {boolean}
     */
    updateBoard(move) {
        const x = move.getX();
        const y = move.getY();
        const mark = move.getSymbol();

        // Check if position is valid and empty
        if (x >= 0 && x < this.rows && y >= 0 && y < this.columns) {
            if (this.board[x][y] === this.blankSymbol || mark === 0) {
                if (mark === 0) {
                    // Undo move (for AI)
                    this.nMoves--;
                    this.board[x][y] = this.blankSymbol;
                } else {
                    // Make move
                    this.nMoves++;
                    this.board[x][y] = mark.toString().toUpperCase();
                }
                return true;
            }
        }
        return false;
    }

    /**
     * Check if player has won
     * @param {Player} player
     * @returns {boolean}
     */
    isWin(player) {
        const sym = player.getSymbol();

        // Helper function to check if three cells are equal and not blank
        const allEqual = (a, b, c) => {
            return a === b && b === c && a !== this.blankSymbol;
        };

        // Check rows and columns
        for (let i = 0; i < this.rows; i++) {
            // Check row
            if (allEqual(this.board[i][0], this.board[i][1], this.board[i][2]) && 
                this.board[i][0] === sym) {
                return true;
            }
            // Check column
            if (allEqual(this.board[0][i], this.board[1][i], this.board[2][i]) && 
                this.board[0][i] === sym) {
                return true;
            }
        }

        // Check diagonals
        if (allEqual(this.board[0][0], this.board[1][1], this.board[2][2]) && 
            this.board[1][1] === sym) {
            return true;
        }
        if (allEqual(this.board[0][2], this.board[1][1], this.board[2][0]) && 
            this.board[1][1] === sym) {
            return true;
        }

        return false;
    }

    /**
     * Check if game is a draw
     * @param {Player} player
     * @returns {boolean}
     */
    isDraw(player) {
        return this.nMoves === 9 && !this.isWin(player);
    }

    /**
     * Check if game is over
     * @param {Player} player
     * @returns {boolean}
     */
    gameIsOver(player) {
        return this.isWin(player) || this.isDraw(player);
    }

    /**
     * Get all empty cells
     * @returns {Array<[number, number]>}
     */
    getEmptyCells() {
        const empty = [];
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                if (this.board[i][j] === this.blankSymbol) {
                    empty.push([i, j]);
                }
            }
        }
        return empty;
    }

    /**
     * Find winning cells (for highlighting)
     * @param {Player} player
     * @returns {Array<[number, number]>}
     */
    getWinningCells(player) {
        const sym = player.getSymbol();
        const allEqual = (a, b, c) => a === b && b === c && a !== this.blankSymbol;

        // Check rows
        for (let i = 0; i < this.rows; i++) {
            if (allEqual(this.board[i][0], this.board[i][1], this.board[i][2]) && 
                this.board[i][0] === sym) {
                return [[i, 0], [i, 1], [i, 2]];
            }
        }

        // Check columns
        for (let i = 0; i < this.columns; i++) {
            if (allEqual(this.board[0][i], this.board[1][i], this.board[2][i]) && 
                this.board[0][i] === sym) {
                return [[0, i], [1, i], [2, i]];
            }
        }

        // Check diagonals
        if (allEqual(this.board[0][0], this.board[1][1], this.board[2][2]) && 
            this.board[1][1] === sym) {
            return [[0, 0], [1, 1], [2, 2]];
        }
        if (allEqual(this.board[0][2], this.board[1][1], this.board[2][0]) && 
            this.board[1][1] === sym) {
            return [[0, 2], [1, 1], [2, 0]];
        }

        return [];
    }
}

// ============================================
// MINIMAX AI PLAYER FOR TIC TAC TOE
// ============================================

class TicTacToeAIPlayer extends Player {
    constructor(name, symbol) {
        super(name, symbol, PlayerType.AI);
    }

    /**
     * Get best move using Minimax algorithm
     * @returns {Move}
     */
    getMove() {
        if (!this.boardPtr) return null;

        const board = this.boardPtr;
        const emptyCells = board.getEmptyCells();

        if (emptyCells.length === 0) return null;

        // If first move, choose center or random corner
        if (board.getMoveCount() === 0) {
            const firstMoves = [[1, 1], [0, 0], [0, 2], [2, 0], [2, 2]];
            const [x, y] = firstMoves[Math.floor(Math.random() * firstMoves.length)];
            return new Move(x, y, this.symbol);
        }

        let bestScore = -Infinity;
        let bestMove = null;

        for (const [x, y] of emptyCells) {
            // Try this move
            board.board[x][y] = this.symbol;
            board.nMoves++;

            // Calculate score
            const score = this.minimax(board, 0, false, -Infinity, Infinity);

            // Undo move
            board.board[x][y] = board.blankSymbol;
            board.nMoves--;

            if (score > bestScore) {
                bestScore = score;
                bestMove = [x, y];
            }
        }

        return bestMove ? new Move(bestMove[0], bestMove[1], this.symbol) : null;
    }

    /**
     * Minimax algorithm with alpha-beta pruning
     * @param {TicTacToeBoard} board
     * @param {number} depth
     * @param {boolean} isMaximizing
     * @param {number} alpha
     * @param {number} beta
     * @returns {number}
     */
    minimax(board, depth, isMaximizing, alpha, beta) {
        // Create temporary players for checking win conditions
        const aiPlayer = { getSymbol: () => this.symbol };
        const humanSymbol = this.symbol === 'X' ? 'O' : 'X';
        const humanPlayer = { getSymbol: () => humanSymbol };

        // Check terminal states
        if (board.isWin(aiPlayer)) return 10 - depth;
        if (board.isWin(humanPlayer)) return depth - 10;
        if (board.isDraw(aiPlayer)) return 0;

        const emptyCells = board.getEmptyCells();

        if (isMaximizing) {
            let maxScore = -Infinity;

            for (const [x, y] of emptyCells) {
                board.board[x][y] = this.symbol;
                board.nMoves++;

                const score = this.minimax(board, depth + 1, false, alpha, beta);

                board.board[x][y] = board.blankSymbol;
                board.nMoves--;

                maxScore = Math.max(maxScore, score);
                alpha = Math.max(alpha, score);

                if (beta <= alpha) break; // Alpha-beta pruning
            }

            return maxScore;
        } else {
            let minScore = Infinity;

            for (const [x, y] of emptyCells) {
                board.board[x][y] = humanSymbol;
                board.nMoves++;

                const score = this.minimax(board, depth + 1, true, alpha, beta);

                board.board[x][y] = board.blankSymbol;
                board.nMoves--;

                minScore = Math.min(minScore, score);
                beta = Math.min(beta, score);

                if (beta <= alpha) break; // Alpha-beta pruning
            }

            return minScore;
        }
    }
}

// ============================================
// TIC TAC TOE UI CLASS
// ============================================

class TicTacToeUI extends UI {
    constructor() {
        super();
    }

    /**
     * Display the board in the DOM
     * @param {TicTacToeBoard} board
     */
    displayBoard(board) {
        this.boardContainer.innerHTML = '';

        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-3';

        const matrix = board.getBoardMatrix();

        for (let i = 0; i < board.getRows(); i++) {
            for (let j = 0; j < board.getColumns(); j++) {
                const value = matrix[i][j];
                const displayValue = (value === '.' || value === null) ? '' : value;

                const cell = this.createCell(i, j, displayValue, (row, col) => {
                    // Only allow click if cell is empty and game is not over
                    if (window.gameManager && !window.gameManager.isGameOver()) {
                        const currentPlayer = window.gameManager.getCurrentPlayer();
                        
                        // Only process if it's a human player's turn
                        if (currentPlayer.getType() === PlayerType.HUMAN) {
                            const move = new Move(row, col, currentPlayer.getSymbol());
                            window.gameManager.processMove(move);
                        }
                    }
                });

                boardDiv.appendChild(cell);
            }
        }

        this.boardContainer.appendChild(boardDiv);
    }
}

// ============================================
// GAME INITIALIZATION
// ============================================

/**
 * Initialize and start Tic Tac Toe game
 * @param {Object} player1Config - {name, type}
 * @param {Object} player2Config - {name, type}
 */
function initTicTacToe(player1Config, player2Config) {
    // Create board
    const board = new TicTacToeBoard();

    // Create players
    const players = [];
    
    // Player 1 (X)
    if (player1Config.type === 'human') {
        players.push(new Player(player1Config.name, 'X', PlayerType.HUMAN));
    } else if (player1Config.type === 'random') {
        players.push(new RandomAIPlayer(player1Config.name, 'X'));
    } else {
        players.push(new TicTacToeAIPlayer(player1Config.name, 'X'));
    }

    // Player 2 (O)
    if (player2Config.type === 'human') {
        players.push(new Player(player2Config.name, 'O', PlayerType.HUMAN));
    } else if (player2Config.type === 'random') {
        players.push(new RandomAIPlayer(player2Config.name, 'O'));
    } else {
        players.push(new TicTacToeAIPlayer(player2Config.name, 'O'));
    }

    // Create UI
    const ui = new TicTacToeUI();

    // Create game manager
    const gameManager = new GameManager(board, players, ui);

    // Display initial board
    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    // Update player info display
    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    // If first player is AI, make their move
    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

// Expose to window for access from main.js
if (typeof window !== 'undefined') {
    window.TicTacToeBoard = TicTacToeBoard;
    window.TicTacToeAIPlayer = TicTacToeAIPlayer;
    window.TicTacToeUI = TicTacToeUI;
    window.initTicTacToe = initTicTacToe;
}

