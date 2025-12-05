/**
 * fourinarow.js
 * Four in a Row (Connect 4) game with Minimax AI
 * Converted from C++ Four_in_a_row.cpp
 */

// ============================================
// FOUR IN A ROW BOARD CLASS
// ============================================

class FourInARowBoard extends Board {
    constructor() {
        super(6, 7); // 6 rows x 7 columns
        this.blankSymbol = '.';
        
        // Initialize board with blank symbols
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blankSymbol;
            }
        }
    }

    /**
     * Update the board with a move (piece drops to lowest available row in column)
     * @param {Move} move - move.y is the column
     * @returns {boolean}
     */
    updateBoard(move) {
        const col = move.getY();
        const mark = move.getSymbol();

        if (col < 0 || col >= this.columns) return false;

        // Find the lowest empty row in this column
        for (let row = this.rows - 1; row >= 0; row--) {
            if (this.board[row][col] === this.blankSymbol) {
                this.board[row][col] = mark.toString().toUpperCase();
                this.nMoves++;
                return true;
            }
        }

        return false; // Column is full
    }

    /**
     * Check if player has won (4 in a row)
     * @param {Player} player
     * @returns {boolean}
     */
    isWin(player) {
        const sym = player.getSymbol();
        return this.checkWinForSymbol(sym);
    }

    /**
     * Check if a specific symbol has 4 in a row
     * @param {string} sym
     * @returns {boolean}
     */
    checkWinForSymbol(sym) {
        // Horizontal
        for (let r = 0; r < this.rows; r++) {
            for (let c = 0; c <= this.columns - 4; c++) {
                if (this.board[r][c] === sym && 
                    this.board[r][c + 1] === sym &&
                    this.board[r][c + 2] === sym && 
                    this.board[r][c + 3] === sym) {
                    return true;
                }
            }
        }

        // Vertical
        for (let c = 0; c < this.columns; c++) {
            for (let r = 0; r <= this.rows - 4; r++) {
                if (this.board[r][c] === sym && 
                    this.board[r + 1][c] === sym &&
                    this.board[r + 2][c] === sym && 
                    this.board[r + 3][c] === sym) {
                    return true;
                }
            }
        }

        // Diagonal (top-left to bottom-right)
        for (let r = 0; r <= this.rows - 4; r++) {
            for (let c = 0; c <= this.columns - 4; c++) {
                if (this.board[r][c] === sym && 
                    this.board[r + 1][c + 1] === sym &&
                    this.board[r + 2][c + 2] === sym && 
                    this.board[r + 3][c + 3] === sym) {
                    return true;
                }
            }
        }

        // Diagonal (bottom-left to top-right)
        for (let r = 3; r < this.rows; r++) {
            for (let c = 0; c <= this.columns - 4; c++) {
                if (this.board[r][c] === sym && 
                    this.board[r - 1][c + 1] === sym &&
                    this.board[r - 2][c + 2] === sym && 
                    this.board[r - 3][c + 3] === sym) {
                    return true;
                }
            }
        }

        return false;
    }

    /**
     * Check if game is a draw (board full, no winner)
     * @param {Player} player
     * @returns {boolean}
     */
    isDraw(player) {
        // Check if top row is full
        for (let c = 0; c < this.columns; c++) {
            if (this.board[0][c] === this.blankSymbol) {
                return false;
            }
        }
        return true;
    }

    /**
     * Get all valid columns where a piece can be placed
     * @returns {number[]}
     */
    getValidColumns() {
        const valid = [];
        for (let c = 0; c < this.columns; c++) {
            if (this.board[0][c] === this.blankSymbol) {
                valid.push(c);
            }
        }
        return valid;
    }

    /**
     * Count sequences of a given length for a symbol
     * @param {string} symbol
     * @param {number} length
     * @returns {number}
     */
    countSequences(symbol, length) {
        let count = 0;

        // Helper to check if a sequence exists starting at (r, c) in direction (dr, dc)
        const checkSequence = (r, c, dr, dc) => {
            for (let i = 0; i < length; i++) {
                const nr = r + i * dr;
                const nc = c + i * dc;
                if (nr < 0 || nr >= this.rows || nc < 0 || nc >= this.columns) {
                    return false;
                }
                if (this.board[nr][nc] !== symbol) {
                    return false;
                }
            }
            return true;
        };

        // Check all positions and directions
        for (let r = 0; r < this.rows; r++) {
            for (let c = 0; c < this.columns; c++) {
                // Horizontal
                if (checkSequence(r, c, 0, 1)) count++;
                // Vertical
                if (checkSequence(r, c, 1, 0)) count++;
                // Diagonal (backslash)
                if (checkSequence(r, c, 1, 1)) count++;
                // Diagonal (forward slash)
                if (checkSequence(r, c, -1, 1)) count++;
            }
        }

        return count;
    }

    /**
     * Evaluate the board for AI (heuristic function)
     * @param {string} aiSymbol
     * @returns {number}
     */
    evaluateBoard(aiSymbol) {
        const humanSymbol = aiSymbol === 'X' ? 'O' : 'X';

        // Check for winning condition
        if (this.checkWinForSymbol(aiSymbol)) return 100000;
        if (this.checkWinForSymbol(humanSymbol)) return -100000;

        let score = 0;

        // Count AI sequences
        const ai4 = this.countSequences(aiSymbol, 4);
        const ai3 = this.countSequences(aiSymbol, 3);
        const ai2 = this.countSequences(aiSymbol, 2);

        // Count Human sequences
        const human4 = this.countSequences(humanSymbol, 4);
        const human3 = this.countSequences(humanSymbol, 3);
        const human2 = this.countSequences(humanSymbol, 2);

        // Scoring weights
        score += ai4 * 1000;
        score += ai3 * 100;
        score += ai2 * 10;

        score -= human4 * 1000;
        score -= human3 * 100;
        score -= human2 * 10;

        // Center column preference
        for (let r = 0; r < this.rows; r++) {
            if (this.board[r][3] === aiSymbol) score += 3;
        }

        return score;
    }

    /**
     * Undo a move in a column (for minimax)
     * @param {number} col
     */
    undoMove(col) {
        for (let row = 0; row < this.rows; row++) {
            if (this.board[row][col] !== this.blankSymbol) {
                this.board[row][col] = this.blankSymbol;
                this.nMoves--;
                return;
            }
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
        // Terminal conditions
        if (this.checkWinForSymbol(aiSymbol)) return 100000 - depth;
        if (this.checkWinForSymbol(humanSymbol)) return -100000 + depth;
        if (depth === 0 || this.isDraw(null)) return this.evaluateBoard(aiSymbol);

        const validCols = this.getValidColumns();

        if (maximizing) {
            let maxEval = -Infinity;

            for (const col of validCols) {
                // Make move
                let row = -1;
                for (let r = this.rows - 1; r >= 0; r--) {
                    if (this.board[r][col] === this.blankSymbol) {
                        this.board[r][col] = aiSymbol;
                        this.nMoves++;
                        row = r;
                        break;
                    }
                }

                if (row !== -1) {
                    const evalScore = this.minimax(depth - 1, false, aiSymbol, humanSymbol, alpha, beta);

                    // Undo move
                    this.board[row][col] = this.blankSymbol;
                    this.nMoves--;

                    maxEval = Math.max(maxEval, evalScore);
                    alpha = Math.max(alpha, evalScore);

                    if (beta <= alpha) break; // Pruning
                }
            }

            return maxEval;
        } else {
            let minEval = Infinity;

            for (const col of validCols) {
                // Make move
                let row = -1;
                for (let r = this.rows - 1; r >= 0; r--) {
                    if (this.board[r][col] === this.blankSymbol) {
                        this.board[r][col] = humanSymbol;
                        this.nMoves++;
                        row = r;
                        break;
                    }
                }

                if (row !== -1) {
                    const evalScore = this.minimax(depth - 1, true, aiSymbol, humanSymbol, alpha, beta);

                    // Undo move
                    this.board[row][col] = this.blankSymbol;
                    this.nMoves--;

                    minEval = Math.min(minEval, evalScore);
                    beta = Math.min(beta, evalScore);

                    if (beta <= alpha) break; // Pruning
                }
            }

            return minEval;
        }
    }

    /**
     * Get the best move for AI using minimax
     * @param {string} aiSymbol
     * @param {string} humanSymbol
     * @returns {number} - Best column
     */
    getBestMove(aiSymbol, humanSymbol) {
        let bestCol = -1;
        let bestValue = -Infinity;
        const depth = 6; // Search depth (adjust for difficulty)

        let validCols = this.getValidColumns();

        // Prioritize center column
        const centerIndex = validCols.indexOf(3);
        if (centerIndex !== -1) {
            validCols.splice(centerIndex, 1);
            validCols.unshift(3);
        }

        for (const col of validCols) {
            // Make move
            let row = -1;
            for (let r = this.rows - 1; r >= 0; r--) {
                if (this.board[r][col] === this.blankSymbol) {
                    this.board[r][col] = aiSymbol;
                    this.nMoves++;
                    row = r;
                    break;
                }
            }

            if (row !== -1) {
                const moveValue = this.minimax(depth - 1, false, aiSymbol, humanSymbol, -Infinity, Infinity);

                // Undo move
                this.board[row][col] = this.blankSymbol;
                this.nMoves--;

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestCol = col;
                }
            }
        }

        return bestCol;
    }
}

// ============================================
// FOUR IN A ROW AI PLAYER
// ============================================

class FourInARowAIPlayer extends Player {
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
        const humanSymbol = this.symbol === 'X' ? 'O' : 'X';

        const bestCol = board.getBestMove(aiSymbol, humanSymbol);

        if (bestCol !== -1) {
            return new Move(0, bestCol, this.symbol);
        }

        return null;
    }
}

// ============================================
// FOUR IN A ROW UI CLASS
// ============================================

class FourInARowUI extends UI {
    constructor() {
        super();
    }

    /**
     * Display the board in the DOM
     * @param {FourInARowBoard} board
     */
    displayBoard(board) {
        this.boardContainer.innerHTML = '';

        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-7';
        boardDiv.style.gridTemplateRows = `repeat(6, 1fr)`;

        const matrix = board.getBoardMatrix();

        for (let i = 0; i < board.getRows(); i++) {
            for (let j = 0; j < board.getColumns(); j++) {
                const value = matrix[i][j];
                const displayValue = (value === '.' || value === null) ? '' : value;

                const cell = this.createCell(i, j, displayValue, (row, col) => {
                    // Click on any row in the column to drop piece
                    if (window.gameManager && !window.gameManager.isGameOver()) {
                        const currentPlayer = window.gameManager.getCurrentPlayer();
                        
                        // Only process if it's a human player's turn
                        if (currentPlayer.getType() === PlayerType.HUMAN) {
                            const move = new Move(0, col, currentPlayer.getSymbol());
                            window.gameManager.processMove(move);
                        }
                    }
                });

                // Add visual indicator for column
                cell.addEventListener('mouseenter', () => {
                    if (window.gameManager && !window.gameManager.isGameOver()) {
                        const currentPlayer = window.gameManager.getCurrentPlayer();
                        if (currentPlayer.getType() === PlayerType.HUMAN) {
                            // Highlight column
                            document.querySelectorAll(`[data-col="${j}"]`).forEach(c => {
                                if (!c.classList.contains('occupied')) {
                                    c.style.background = 'rgba(108, 99, 255, 0.3)';
                                }
                            });
                        }
                    }
                });

                cell.addEventListener('mouseleave', () => {
                    document.querySelectorAll(`[data-col="${j}"]`).forEach(c => {
                        c.style.background = '';
                    });
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
 * Initialize and start Four in a Row game
 * @param {Object} player1Config
 * @param {Object} player2Config
 */
function initFourInARow(player1Config, player2Config) {
    // Create board
    const board = new FourInARowBoard();

    // Create players
    const players = [];
    
    // Player 1 (X)
    if (player1Config.type === 'human') {
        players.push(new Player(player1Config.name, 'X', PlayerType.HUMAN));
    } else if (player1Config.type === 'random') {
        players.push(new RandomAIPlayer(player1Config.name, 'X'));
    } else {
        players.push(new FourInARowAIPlayer(player1Config.name, 'X'));
    }

    // Player 2 (O)
    if (player2Config.type === 'human') {
        players.push(new Player(player2Config.name, 'O', PlayerType.HUMAN));
    } else if (player2Config.type === 'random') {
        players.push(new RandomAIPlayer(player2Config.name, 'O'));
    } else {
        players.push(new FourInARowAIPlayer(player2Config.name, 'O'));
    }

    // Create UI
    const ui = new FourInARowUI();

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
        setTimeout(() => gameManager.makeAIMove(), 1000);
    }

    return gameManager;
}

// Expose to window
if (typeof window !== 'undefined') {
    window.FourInARowBoard = FourInARowBoard;
    window.FourInARowAIPlayer = FourInARowAIPlayer;
    window.FourInARowUI = FourInARowUI;
    window.initFourInARow = initFourInARow;
}


