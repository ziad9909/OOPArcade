/**
 * 4x4.js
 * 4x4 Tic Tac Toe with piece movement
 */

class FourByFourBoard extends Board {
    constructor() {
        super(4, 4);
        this.blank = '.';
        
        // Initialize board
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blank;
            }
        }

        // Starting positions
        this.board[0][1] = 'X';
        this.board[0][3] = 'X';
        this.board[3][0] = 'X';
        this.board[3][2] = 'X';

        this.board[0][0] = 'O';
        this.board[0][2] = 'O';
        this.board[3][1] = 'O';
        this.board[3][3] = 'O';
    }

    updateBoard(move) {
        // For simplicity, just place pieces in empty cells
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

        // Check rows (3 in a row on 4x4 board)
        for (let i = 0; i < 4; i++) {
            for (let j = 0; j < 2; j++) {
                if (this.board[i][j] === s && this.board[i][j + 1] === s && this.board[i][j + 2] === s) {
                    return true;
                }
            }
        }

        // Check columns
        for (let j = 0; j < 4; j++) {
            for (let i = 0; i < 2; i++) {
                if (this.board[i][j] === s && this.board[i + 1][j] === s && this.board[i + 2][j] === s) {
                    return true;
                }
            }
        }

        // Check diagonals
        for (let i = 0; i < 2; i++) {
            for (let j = 0; j < 2; j++) {
                if (this.board[i][j] === s && this.board[i + 1][j + 1] === s && this.board[i + 2][j + 2] === s) {
                    return true;
                }
            }
        }

        for (let i = 2; i < 4; i++) {
            for (let j = 0; j < 2; j++) {
                if (this.board[i][j] === s && this.board[i - 1][j + 1] === s && this.board[i - 2][j + 2] === s) {
                    return true;
                }
            }
        }

        return false;
    }

    isDraw(player) {
        let emptyCount = 0;
        for (let i = 0; i < 4; i++) {
            for (let j = 0; j < 4; j++) {
                if (this.board[i][j] === this.blank) emptyCount++;
            }
        }
        return emptyCount === 0 && !this.isWin(player);
    }
}

class FourByFourUI extends TicTacToeUI {
    displayBoard(board) {
        this.boardContainer.innerHTML = '';
        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-4';

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

                cell.style.width = '70px';
                cell.style.height = '70px';
                boardDiv.appendChild(cell);
            }
        }
        this.boardContainer.appendChild(boardDiv);
    }
}

function init4x4TTT(player1Config, player2Config) {
    const board = new FourByFourBoard();
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

    const ui = new FourByFourUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `<p><strong>4x4 Board:</strong> Get 3 in a row to win!</p>`;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.init4x4TTT = init4x4TTT;
}


