/**
 * numerical.js
 * Numerical Tic Tac Toe - Players use numbers 1-9, win by making any line sum to 15
 * Converted from C++ Numerical_TTT_Classes.cpp
 */

// ============================================
// NUMERICAL TIC TAC TOE BOARD CLASS
// ============================================

class NumericalTTTBoard extends Board {
    constructor() {
        super(3, 3);
        
        // Initialize board with 0 (representing empty)
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = 0;
            }
        }

        // Available numbers for each player
        this.oddNums = [1, 3, 5, 7, 9];   // Player 1
        this.evenNums = [2, 4, 6, 8];     // Player 2
    }

    /**
     * Update the board with a numbered move
     * @param {Move} move - move.symbol is the number to place
     * @returns {boolean}
     */
    updateBoard(move) {
        const x = move.getX();
        const y = move.getY();
        const num = move.getSymbol();

        // Check if position is valid and empty
        if (x < 0 || x >= this.rows || y < 0 || y >= this.columns || this.board[x][y] !== 0) {
            return false;
        }

        // Determine which list to check based on odd/even
        let targetList;
        if (num % 2 !== 0) {
            targetList = this.oddNums;
        } else {
            targetList = this.evenNums;
        }

        // Check if number is available
        const index = targetList.indexOf(num);
        if (index === -1) {
            return false;
        }

        // Apply the move
        this.board[x][y] = num;
        targetList.splice(index, 1); // Remove from available list
        this.nMoves++;
        return true;
    }

    /**
     * Check if any line sums to 15 (win condition)
     * @param {Player} player
     * @returns {boolean}
     */
    isWin(player) {
        return this.checkWin();
    }

    /**
     * Helper function to check all lines for sum of 15
     * @returns {boolean}
     */
    checkWin() {
        // Check rows
        for (let i = 0; i < 3; i++) {
            if (this.board[i][0] !== 0 && this.board[i][1] !== 0 && this.board[i][2] !== 0) {
                if (this.board[i][0] + this.board[i][1] + this.board[i][2] === 15) {
                    return true;
                }
            }
        }

        // Check columns
        for (let j = 0; j < 3; j++) {
            if (this.board[0][j] !== 0 && this.board[1][j] !== 0 && this.board[2][j] !== 0) {
                if (this.board[0][j] + this.board[1][j] + this.board[2][j] === 15) {
                    return true;
                }
            }
        }

        // Check main diagonal
        if (this.board[0][0] !== 0 && this.board[1][1] !== 0 && this.board[2][2] !== 0) {
            if (this.board[0][0] + this.board[1][1] + this.board[2][2] === 15) {
                return true;
            }
        }

        // Check anti-diagonal
        if (this.board[0][2] !== 0 && this.board[1][1] !== 0 && this.board[2][0] !== 0) {
            if (this.board[0][2] + this.board[1][1] + this.board[2][0] === 15) {
                return true;
            }
        }

        return false;
    }

    /**
     * Check if game is a draw (all 9 moves made, no winner)
     * @param {Player} player
     * @returns {boolean}
     */
    isDraw(player) {
        return this.nMoves === 9 && !this.isWin(player);
    }

    /**
     * Get available numbers for a player
     * @param {number} playerSymbol - 1 for Odd, 2 for Even
     * @returns {number[]}
     */
    getAvailableNumbers(playerSymbol) {
        if (playerSymbol === 1) {
            return [...this.oddNums];
        } else {
            return [...this.evenNums];
        }
    }

    /**
     * Find winning lines (for highlighting)
     * @returns {Array<[number, number]>}
     */
    getWinningCells() {
        // Check rows
        for (let i = 0; i < 3; i++) {
            if (this.board[i][0] !== 0 && this.board[i][1] !== 0 && this.board[i][2] !== 0) {
                if (this.board[i][0] + this.board[i][1] + this.board[i][2] === 15) {
                    return [[i, 0], [i, 1], [i, 2]];
                }
            }
        }

        // Check columns
        for (let j = 0; j < 3; j++) {
            if (this.board[0][j] !== 0 && this.board[1][j] !== 0 && this.board[2][j] !== 0) {
                if (this.board[0][j] + this.board[1][j] + this.board[2][j] === 15) {
                    return [[0, j], [1, j], [2, j]];
                }
            }
        }

        // Check main diagonal
        if (this.board[0][0] !== 0 && this.board[1][1] !== 0 && this.board[2][2] !== 0) {
            if (this.board[0][0] + this.board[1][1] + this.board[2][2] === 15) {
                return [[0, 0], [1, 1], [2, 2]];
            }
        }

        // Check anti-diagonal
        if (this.board[0][2] !== 0 && this.board[1][1] !== 0 && this.board[2][0] !== 0) {
            if (this.board[0][2] + this.board[1][1] + this.board[2][0] === 15) {
                return [[0, 2], [1, 1], [2, 0]];
            }
        }

        return [];
    }
}

// ============================================
// NUMERICAL TTT AI PLAYER (Random)
// ============================================

class NumericalTTTRandomPlayer extends Player {
    constructor(name, symbol) {
        super(name, symbol, PlayerType.RANDOM);
    }

    /**
     * Get a random move
     * @returns {Move}
     */
    getMove() {
        if (!this.boardPtr) return null;

        const board = this.boardPtr;
        
        // Get available numbers
        const availableNums = board.getAvailableNumbers(this.symbol);
        if (availableNums.length === 0) return null;

        // Pick a random number
        const num = availableNums[Math.floor(Math.random() * availableNums.length)];

        // Find empty cells
        const emptyCells = [];
        for (let i = 0; i < board.getRows(); i++) {
            for (let j = 0; j < board.getColumns(); j++) {
                if (board.getCell(i, j) === 0) {
                    emptyCells.push([i, j]);
                }
            }
        }

        // Pick a random empty cell
        if (emptyCells.length > 0) {
            const [x, y] = emptyCells[Math.floor(Math.random() * emptyCells.length)];
            return new Move(x, y, num);
        }

        return null;
    }
}

// ============================================
// NUMERICAL TTT UI CLASS
// ============================================

class NumericalTTTUI extends UI {
    constructor() {
        super();
        this.selectedNumber = null;
    }

    /**
     * Display the board in the DOM
     * @param {NumericalTTTBoard} board
     */
    displayBoard(board) {
        this.boardContainer.innerHTML = '';

        const container = document.createElement('div');
        container.style.display = 'flex';
        container.style.flexDirection = 'column';
        container.style.alignItems = 'center';
        container.style.gap = '20px';

        // Number selection area
        const numberSelection = document.createElement('div');
        numberSelection.id = 'number-selection';
        numberSelection.style.display = 'flex';
        numberSelection.style.gap = '10px';
        numberSelection.style.flexWrap = 'wrap';
        numberSelection.style.justifyContent = 'center';
        numberSelection.style.padding = '15px';
        numberSelection.style.background = '#FFFFFF';
        numberSelection.style.border = '1px solid #E1E8ED';
        numberSelection.style.borderRadius = '12px';
        numberSelection.style.maxWidth = '400px';
        numberSelection.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.08)';

        container.appendChild(numberSelection);

        // Game board
        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-3';

        const matrix = board.getBoardMatrix();

        for (let i = 0; i < board.getRows(); i++) {
            for (let j = 0; j < board.getColumns(); j++) {
                const value = matrix[i][j];
                const displayValue = value === 0 ? '' : value;

                const cell = this.createCell(i, j, displayValue, (row, col) => {
                    if (window.gameManager && !window.gameManager.isGameOver()) {
                        const currentPlayer = window.gameManager.getCurrentPlayer();
                        
                        if (currentPlayer.getType() === PlayerType.HUMAN) {
                            // Need to select a number first
                            if (this.selectedNumber === null) {
                                this.displayMessage('Please select a number first!', 'info');
                                return;
                            }

                            const move = new Move(row, col, this.selectedNumber);
                            if (window.gameManager.processMove(move)) {
                                this.selectedNumber = null;
                                this.updateNumberSelection(board);
                            }
                        }
                    }
                });

                boardDiv.appendChild(cell);
            }
        }

        container.appendChild(boardDiv);
        this.boardContainer.appendChild(container);

        // Update number selection
        this.updateNumberSelection(board);
    }

    /**
     * Update the number selection area
     * @param {NumericalTTTBoard} board
     */
    updateNumberSelection(board) {
        const numberSelection = document.getElementById('number-selection');
        if (!numberSelection || !window.gameManager) return;

        numberSelection.innerHTML = '';

        const currentPlayer = window.gameManager.getCurrentPlayer();
        
        // Only show number selection for human players
        if (currentPlayer.getType() !== PlayerType.HUMAN) {
            numberSelection.innerHTML = '<div style="color: var(--text-secondary);">AI is thinking...</div>';
            return;
        }

        const availableNums = board.getAvailableNumbers(currentPlayer.getSymbol());

        if (availableNums.length === 0) {
            numberSelection.innerHTML = '<div style="color: var(--text-secondary);">No numbers available</div>';
            return;
        }

        const title = document.createElement('div');
        title.textContent = 'Select a number:';
        title.style.width = '100%';
        title.style.textAlign = 'center';
        title.style.marginBottom = '10px';
        title.style.fontWeight = 'bold';
        numberSelection.appendChild(title);

        availableNums.forEach(num => {
            const btn = document.createElement('button');
            btn.textContent = num;
            btn.className = 'number-btn';
            btn.style.width = '50px';
            btn.style.height = '50px';
            btn.style.fontSize = '1.5rem';
            btn.style.fontWeight = 'bold';
            btn.style.border = '1px solid #E1E8ED';
            btn.style.borderRadius = '8px';
            btn.style.background = '#FFFFFF';
            btn.style.color = '#2C3E50';
            btn.style.cursor = 'pointer';
            btn.style.transition = 'all 0.3s ease';
            btn.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.08)';

            if (this.selectedNumber === num) {
                btn.style.borderColor = '#4DA6FF';
                btn.style.background = 'rgba(77, 166, 255, 0.15)';
                btn.style.transform = 'scale(1.1)';
                btn.style.boxShadow = '0 0 0 3px rgba(77, 166, 255, 0.1)';
            }

            btn.addEventListener('mouseenter', () => {
                btn.style.borderColor = '#4DA6FF';
                btn.style.transform = 'scale(1.05)';
                btn.style.boxShadow = '0 4px 12px rgba(0, 0, 0, 0.1)';
            });

            btn.addEventListener('mouseleave', () => {
                if (this.selectedNumber !== num) {
                    btn.style.borderColor = '#E1E8ED';
                    btn.style.transform = 'scale(1)';
                    btn.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.08)';
                }
            });

            btn.addEventListener('click', () => {
                this.selectedNumber = num;
                this.updateNumberSelection(board);
                this.clearMessage();
            });

            numberSelection.appendChild(btn);
        });
    }

    /**
     * Override updateTurnIndicator to also update number selection
     * @param {Player} player
     */
    updateTurnIndicator(player) {
        super.updateTurnIndicator(player);
        if (this.boardContainer && window.gameManager) {
            const board = window.gameManager.board;
            this.updateNumberSelection(board);
        }
    }
}

// ============================================
// GAME INITIALIZATION
// ============================================

/**
 * Initialize and start Numerical Tic Tac Toe game
 * @param {Object} player1Config
 * @param {Object} player2Config
 */
function initNumericalTTT(player1Config, player2Config) {
    // Create board
    const board = new NumericalTTTBoard();

    // Create players
    const players = [];
    
    // Player 1 (Odd numbers - symbol 1)
    if (player1Config.type === 'human') {
        players.push(new Player(player1Config.name, 1, PlayerType.HUMAN));
    } else {
        players.push(new NumericalTTTRandomPlayer(player1Config.name, 1));
    }

    // Player 2 (Even numbers - symbol 2)
    if (player2Config.type === 'human') {
        players.push(new Player(player2Config.name, 2, PlayerType.HUMAN));
    } else {
        players.push(new NumericalTTTRandomPlayer(player2Config.name, 2));
    }

    // Create UI
    const ui = new NumericalTTTUI();
// Create game manager
const gameManager = new GameManager(board, players, ui);

// ربط gameManager بالـ window قبل أي تحديث للواجهة
window.gameManager = gameManager;

// Display initial board
ui.displayBoard(board);

// إذا كان اللاعب الأول بشري، نحدث واجهة اختيار الرقم
if (players[0].getType() === PlayerType.HUMAN) {
    ui.updateNumberSelection(board);
}

// Update turn indicator
ui.updateTurnIndicator(players[0]);

// Update player info display
document.querySelector('#player1-info .player-name').textContent = player1Config.name;
document.querySelector('#player1-info .player-symbol').textContent = 'ODD';
document.querySelector('#player2-info .player-name').textContent = player2Config.name;
document.querySelector('#player2-info .player-symbol').textContent = 'EVEN';

    // Add info about the game
    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `
            <p><strong>How to play:</strong> Make any row, column, or diagonal sum to exactly 15 to win!</p>
            <p>Player 1 uses odd numbers (1, 3, 5, 7, 9) • Player 2 uses even numbers (2, 4, 6, 8)</p>
        `;
    }

    // If first player is AI, make their move
    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 1000);
    }

    return gameManager;
}

// Expose to window
if (typeof window !== 'undefined') {
    window.NumericalTTTBoard = NumericalTTTBoard;
    window.NumericalTTTRandomPlayer = NumericalTTTRandomPlayer;
    window.NumericalTTTUI = NumericalTTTUI;
    window.initNumericalTTT = initNumericalTTT;
}


