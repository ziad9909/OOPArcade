/**
 * obstacle.js
 * 6x6 Tic Tac Toe with obstacles
 */

class ObstacleBoard extends Board {
    constructor() {
        super(6, 6);
        this.blank = '.';
        this.obstacle = '#';
        
        // Initialize board
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blank;
            }
        }

        // Place obstacles randomly
        const obstaclePositions = [
            [1, 2], [2, 1], [2, 4], [3, 3], [4, 2], [4, 4]
        ];

        obstaclePositions.forEach(([x, y]) => {
            this.board[x][y] = this.obstacle;
        });
    }

    updateBoard(move) {
        const x = move.getX();
        const y = move.getY();
        const mark = move.getSymbol();

        if (x >= 0 && x < this.rows && y >= 0 && y < this.columns && 
            this.board[x][y] === this.blank) {
            this.board[x][y] = mark;
            this.nMoves++;
            return true;
        }
        return false;
    }

    isWin(player) {
        const s = player.getSymbol();

        // Check for 4 in a row
        // Rows
        for (let i = 0; i < 6; i++) {
            for (let j = 0; j <= 2; j++) {
                if (this.board[i][j] === s && this.board[i][j + 1] === s && 
                    this.board[i][j + 2] === s && this.board[i][j + 3] === s) {
                    return true;
                }
            }
        }

        // Columns
        for (let j = 0; j < 6; j++) {
            for (let i = 0; i <= 2; i++) {
                if (this.board[i][j] === s && this.board[i + 1][j] === s && 
                    this.board[i + 2][j] === s && this.board[i + 3][j] === s) {
                    return true;
                }
            }
        }

        // Diagonals
        for (let i = 0; i <= 2; i++) {
            for (let j = 0; j <= 2; j++) {
                if (this.board[i][j] === s && this.board[i + 1][j + 1] === s && 
                    this.board[i + 2][j + 2] === s && this.board[i + 3][j + 3] === s) {
                    return true;
                }
            }
        }

        for (let i = 3; i < 6; i++) {
            for (let j = 0; j <= 2; j++) {
                if (this.board[i][j] === s && this.board[i - 1][j + 1] === s && 
                    this.board[i - 2][j + 2] === s && this.board[i - 3][j + 3] === s) {
                    return true;
                }
            }
        }

        return false;
    }

    isDraw(player) {
        let emptyCount = 0;
        for (let i = 0; i < 6; i++) {
            for (let j = 0; j < 6; j++) {
                if (this.board[i][j] === this.blank) emptyCount++;
            }
        }
        return emptyCount === 0 && !this.isWin(player);
    }
}

class ObstacleUI extends UI {
    displayBoard(board) {
        this.boardContainer.innerHTML = '';
        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-6';

        const matrix = board.getBoardMatrix();
        for (let i = 0; i < board.getRows(); i++) {
            for (let j = 0; j < board.getColumns(); j++) {
                const value = matrix[i][j];
                let displayValue = (value === '.' || value === null) ? '' : value;

                const cell = this.createCell(i, j, displayValue === '#' ? '' : displayValue, (row, col) => {
                    if (window.gameManager && !window.gameManager.isGameOver()) {
                        const currentPlayer = window.gameManager.getCurrentPlayer();
                        if (currentPlayer.getType() === PlayerType.HUMAN) {
                            const move = new Move(row, col, currentPlayer.getSymbol());
                            window.gameManager.processMove(move);
                        }
                    }
                });

                if (value === '#') {
                    cell.classList.add('obstacle');
                }

                cell.style.width = '55px';
                cell.style.height = '55px';
                boardDiv.appendChild(cell);
            }
        }
        this.boardContainer.appendChild(boardDiv);
    }
}

function initObstacleTTT(player1Config, player2Config) {
    const board = new ObstacleBoard();
    const players = [];
    
    if (player1Config.type === 'human') {
        players.push(new Player(player1Config.name, 'X', PlayerType.HUMAN));
    } else {
        players.push(new RandomAIPlayer(player1Config.name, 'X'));
    }

    if (player2Config.type === 'human') {
        players.push(new Player(player2Config.name, 'O', PlayerType.HUMAN));
    } else {
        players.push(new RandomAIPlayer(player2Config.name, 'O'));
    }

    const ui = new ObstacleUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `<p><strong>6x6 with Obstacles:</strong> Get 4 in a row, avoid obstacles!</p>`;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.initObstacleTTT = initObstacleTTT;
}

