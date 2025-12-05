/**
 * sus.js
 * SUS Game - Players place 'S' and 'U' letters to form "SUS" sequences
 * Converted from C++ SUS.cpp with Minimax AI
 */

// ============================================
// SUS BOARD CLASS
// ============================================

class SUSBoard extends Board {
    constructor() {
        super(3, 3);
        this.blankSymbol = '.';
        this.scoreS = 0;
        this.scoreU = 0;
        
        // Initialize board
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blankSymbol;
            }
        }
    }

    /**
     * Update the board and calculate new SUS sequences formed
     * @param {Move} move
     * @returns {boolean}
     */
    updateBoard(move) {
        const x = move.getX();
        const y = move.getY();
        const mark = move.getSymbol();

        if (x >= 0 && x < this.rows && y >= 0 && y < this.columns && 
            this.board[x][y] === this.blankSymbol) {
            
            this.board[x][y] = mark.toString().toUpperCase();
            this.nMoves++;

            // Check how many new SUS sequences were formed
            const newSequences = this.checkNewSequences(x, y);

            // Add points to the player who placed this letter
            if (mark === 'S') {
                this.scoreS += newSequences;
            } else if (mark === 'U') {
                this.scoreU += newSequences;
            }

            return true;
        }
        return false;
    }

    /**
     * Check how many SUS sequences were completed by the last move
     * @param {number} x
     * @param {number} y
     * @returns {number}
     */
    checkNewSequences(x, y) {
        let count = 0;

        // Helper to check if three cells form "SUS"
        const isSUS = (r1, c1, r2, c2, r3, c3) => {
            return this.board[r1][c1] === 'S' && 
                   this.board[r2][c2] === 'U' && 
                   this.board[r3][c3] === 'S';
        };

        // Check horizontal (row)
        const row = x;
        if (isSUS(row, 0, row, 1, row, 2)) {
            if (y >= 0 && y <= 2) count++;
        }

        // Check vertical (column)
        const col = y;
        if (isSUS(0, col, 1, col, 2, col)) {
            if (x >= 0 && x <= 2) count++;
        }

        // Check main diagonal (top-left to bottom-right)
        if (x === y) {
            if (isSUS(0, 0, 1, 1, 2, 2)) count++;
        }

        // Check anti-diagonal (top-right to bottom-left)
        if (x + y === 2) {
            if (isSUS(0, 2, 1, 1, 2, 0)) count++;
        }

        return count;
    }

    /**
     * Get score for a player
     * @param {Player} player
     * @returns {number}
     */
    getScore(player) {
        const symbol = player.getSymbol();
        if (symbol === 'S') return this.scoreS;
        if (symbol === 'U') return this.scoreU;
        return 0;
    }

    /**
     * Check if player has won (higher score when board is full)
     * @param {Player} player
     * @returns {boolean}
     */
    isWin(player) {
        if (this.nMoves < 9) return false;

        const otherSymbol = player.getSymbol() === 'S' ? 'U' : 'S';
        
        if (player.getSymbol() === 'S') {
            return this.scoreS > this.scoreU;
        } else {
            return this.scoreU > this.scoreS;
        }
    }

    /**
     * Check if player has lost
     * @param {Player} player
     * @returns {boolean}
     */
    isLose(player) {
        if (this.nMoves < 9) return false;

        if (player.getSymbol() === 'S') {
            return this.scoreS < this.scoreU;
        } else {
            return this.scoreU < this.scoreS;
        }
    }

    /**
     * Check if game is a draw (equal scores when board is full)
     * @param {Player} player
     * @returns {boolean}
     */
    isDraw(player) {
        if (this.nMoves < 9) return false;
        return this.scoreS === this.scoreU;
    }

    /**
     * Check if game is over (board is full)
     * @param {Player} player
     * @returns {boolean}
     */
    gameIsOver(player) {
        return this.nMoves === 9;
    }

    /**
     * Get all empty cells
     * @returns {Array<[number, number]>}
     */
    getEmptyCells() {
        const empty = [];
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                if (this.board[i][j] === '.') {
                    empty.push([i, j]);
                }
            }
        }
        return empty;
    }

    /**
     * Evaluate board state for AI
     * @param {string} aiSymbol
     * @returns {number}
     */
    evaluateState(aiSymbol) {
        if (aiSymbol === 'S') {
            return this.scoreS - this.scoreU;
        } else {
            return this.scoreU - this.scoreS;
        }
    }

    /**
     * Minimax algorithm with alpha-beta pruning
     * @param {number} depth
     * @param {boolean} maximizing
     * @param {string} aiSymbol
     * @param {string} humanSymbol
     * @param {number} alpha
     * @param {number} beta
     * @returns {number}
     */
    minimax(depth, maximizing, aiSymbol, humanSymbol, alpha, beta) {
        if (depth === 0 || this.nMoves === 9) {
            return this.evaluateState(aiSymbol);
        }

        const empty = this.getEmptyCells();

        if (maximizing) {
            let best = -10000;

            for (const [r, c] of empty) {
                // Save state
                const oldScoreS = this.scoreS;
                const oldScoreU = this.scoreU;

                // Make move
                this.board[r][c] = aiSymbol;
                this.nMoves++;

                // Update score
                const newSeq = this.checkNewSequences(r, c);
                if (aiSymbol === 'S') this.scoreS += newSeq;
                else this.scoreU += newSeq;

                // Recurse
                best = Math.max(best, this.minimax(depth - 1, false, aiSymbol, humanSymbol, alpha, beta));

                // Restore state
                this.board[r][c] = '.';
                this.nMoves--;
                this.scoreS = oldScoreS;
                this.scoreU = oldScoreU;

                alpha = Math.max(alpha, best);
                if (beta <= alpha) break;
            }

            return best;
        } else {
            let best = 10000;

            for (const [r, c] of empty) {
                // Save state
                const oldScoreS = this.scoreS;
                const oldScoreU = this.scoreU;

                // Make move
                this.board[r][c] = humanSymbol;
                this.nMoves++;

                // Update score
                const newSeq = this.checkNewSequences(r, c);
                if (humanSymbol === 'S') this.scoreS += newSeq;
                else this.scoreU += newSeq;

                // Recurse
                best = Math.min(best, this.minimax(depth - 1, true, aiSymbol, humanSymbol, alpha, beta));

                // Restore state
                this.board[r][c] = '.';
                this.nMoves--;
                this.scoreS = oldScoreS;
                this.scoreU = oldScoreU;

                beta = Math.min(beta, best);
                if (beta <= alpha) break;
            }

            return best;
        }
    }

    /**
     * Get best move for AI using minimax
     * @param {string} aiSymbol
     * @param {string} humanSymbol
     * @returns {[number, number]}
     */
    getBestMove(aiSymbol, humanSymbol) {
        let bestValue = -10000;
        let bestMove = [-1, -1];

        const empty = this.getEmptyCells();

        for (const [r, c] of empty) {
            // Save state
            const oldScoreS = this.scoreS;
            const oldScoreU = this.scoreU;

            // Make move
            this.board[r][c] = aiSymbol;
            this.nMoves++;

            // Update score
            const newSeq = this.checkNewSequences(r, c);
            if (aiSymbol === 'S') this.scoreS += newSeq;
            else this.scoreU += newSeq;

            // Evaluate
            const val = this.minimax(6, false, aiSymbol, humanSymbol, -10000, 10000);

            // Restore state
            this.board[r][c] = '.';
            this.nMoves--;
            this.scoreS = oldScoreS;
            this.scoreU = oldScoreU;

            if (val > bestValue) {
                bestValue = val;
                bestMove = [r, c];
            }
        }

        return bestMove;
    }
}

// ============================================
// SUS AI PLAYER
// ============================================

class SUSAIPlayer extends Player {
    constructor(name, symbol) {
        super(name, symbol, PlayerType.AI);
    }

    /**
     * Get best move using Minimax
     * @returns {Move}
     */
    getMove() {
        if (!this.boardPtr) return null;

        const board = this.boardPtr;
        const aiSymbol = this.symbol;
        const humanSymbol = this.symbol === 'S' ? 'U' : 'S';

        const [row, col] = board.getBestMove(aiSymbol, humanSymbol);

        if (row !== -1 && col !== -1) {
            return new Move(row, col, this.symbol);
        }

        return null;
    }
}

// ============================================
// SUS UI CLASS
// ============================================

class SUSUI extends UI {
    constructor() {
        super();
    }

    /**
     * Display the board in the DOM
     * @param {SUSBoard} board
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
                    if (window.gameManager && !window.gameManager.isGameOver()) {
                        const currentPlayer = window.gameManager.getCurrentPlayer();
                        
                        if (currentPlayer.getType() === PlayerType.HUMAN) {
                            const move = new Move(row, col, currentPlayer.getSymbol());
                            window.gameManager.processMove(move);
                        }
                    }
                });

                // Color code the letters
                if (displayValue === 'S') {
                    cell.style.color = '#F44336'; // Red for S
                } else if (displayValue === 'U') {
                    cell.style.color = '#4DA6FF'; // Light blue for U
                }

                boardDiv.appendChild(cell);
            }
        }

        this.boardContainer.appendChild(boardDiv);

        // Update scores
        this.updateScores(board);
    }

    /**
     * Update score displays
     * @param {SUSBoard} board
     */
    updateScores(board) {
        const player1Score = document.getElementById('player1-score');
        const player2Score = document.getElementById('player2-score');

        if (player1Score) {
            player1Score.textContent = `Score: ${board.scoreS}`;
        }
        if (player2Score) {
            player2Score.textContent = `Score: ${board.scoreU}`;
        }
    }
}

// ============================================
// GAME INITIALIZATION
// ============================================

/**
 * Initialize and start SUS game
 * @param {Object} player1Config
 * @param {Object} player2Config
 */
function initSUS(player1Config, player2Config) {
    // Create board
    const board = new SUSBoard();

    // Create players
    const players = [];
    
    // Player 1 (S)
    if (player1Config.type === 'human') {
        players.push(new Player(player1Config.name, 'S', PlayerType.HUMAN));
    } else if (player1Config.type === 'random') {
        players.push(new RandomAIPlayer(player1Config.name, 'S'));
    } else {
        players.push(new SUSAIPlayer(player1Config.name, 'S'));
    }

    // Player 2 (U)
    if (player2Config.type === 'human') {
        players.push(new Player(player2Config.name, 'U', PlayerType.HUMAN));
    } else if (player2Config.type === 'random') {
        players.push(new RandomAIPlayer(player2Config.name, 'U'));
    } else {
        players.push(new SUSAIPlayer(player2Config.name, 'U'));
    }

    // Create UI
    const ui = new SUSUI();

    // Create game manager with custom score checking
    const gameManager = new GameManager(board, players, ui);

    // Override the processMove to update scores
    const originalProcessMove = gameManager.processMove.bind(gameManager);
    gameManager.processMove = function(move) {
        const result = originalProcessMove(move);
        if (result) {
            ui.updateScores(board);
        }
        return result;
    };

    // Display initial board
    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    // Update player info display
    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player1-info .player-symbol').textContent = 'S';
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;
    document.querySelector('#player2-info .player-symbol').textContent = 'U';

    // Show scores initially
    ui.updateScores(board);

    // Add info about the game
    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `
            <p><strong>How to play:</strong> Form "SUS" sequences (S-U-S) in any row, column, or diagonal!</p>
            <p>Player 1 places 'S' • Player 2 places 'U' • Highest score wins when board is full!</p>
        `;
    }

    // If first player is AI, make their move
    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

// Expose to window
if (typeof window !== 'undefined') {
    window.SUSBoard = SUSBoard;
    window.SUSAIPlayer = SUSAIPlayer;
    window.SUSUI = SUSUI;
    window.initSUS = initSUS;
}


