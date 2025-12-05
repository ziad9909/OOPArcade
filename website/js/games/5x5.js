/**
 * 5x5.js
 * 5x5 Tic Tac Toe - Count three-in-a-row sequences, most wins!
 */

class FiveByFiveBoard extends Board {
    constructor() {
        super(5, 5);
        this.blank = '.';
        
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blank;
            }
        }
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

    countSequences(symbol) {
        let count = 0;

        // Check rows
        for (let i = 0; i < 5; i++) {
            for (let j = 0; j <= 2; j++) {
                if (this.board[i][j] === symbol && 
                    this.board[i][j + 1] === symbol && 
                    this.board[i][j + 2] === symbol) {
                    count++;
                }
            }
        }

        // Check columns
        for (let j = 0; j < 5; j++) {
            for (let i = 0; i <= 2; i++) {
                if (this.board[i][j] === symbol && 
                    this.board[i + 1][j] === symbol && 
                    this.board[i + 2][j] === symbol) {
                    count++;
                }
            }
        }

        // Check diagonals
        for (let i = 0; i <= 2; i++) {
            for (let j = 0; j <= 2; j++) {
                if (this.board[i][j] === symbol && 
                    this.board[i + 1][j + 1] === symbol && 
                    this.board[i + 2][j + 2] === symbol) {
                    count++;
                }
            }
        }

        for (let i = 2; i < 5; i++) {
            for (let j = 0; j <= 2; j++) {
                if (this.board[i][j] === symbol && 
                    this.board[i - 1][j + 1] === symbol && 
                    this.board[i - 2][j + 2] === symbol) {
                    count++;
                }
            }
        }

        return count;
    }

    isWin(player) {
        if (this.nMoves < 24) return false; // Game ends after 24 moves (5x5-1)

        const playerSeq = this.countSequences(player.getSymbol());
        const opponentSymbol = player.getSymbol() === 'X' ? 'O' : 'X';
        const opponentSeq = this.countSequences(opponentSymbol);

        return playerSeq > opponentSeq;
    }

    isLose(player) {
        if (this.nMoves < 24) return false;

        const playerSeq = this.countSequences(player.getSymbol());
        const opponentSymbol = player.getSymbol() === 'X' ? 'O' : 'X';
        const opponentSeq = this.countSequences(opponentSymbol);

        return playerSeq < opponentSeq;
    }

    isDraw(player) {
        if (this.nMoves < 24) return false;

        const playerSeq = this.countSequences(player.getSymbol());
        const opponentSymbol = player.getSymbol() === 'X' ? 'O' : 'X';
        const opponentSeq = this.countSequences(opponentSymbol);

        return playerSeq === opponentSeq;
    }

    gameIsOver(player) {
        return this.nMoves >= 24;
    }
}

class FiveByFiveUI extends UI {
    displayBoard(board) {
        this.boardContainer.innerHTML = '';
        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-5';

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

                cell.style.width = '60px';
                cell.style.height = '60px';
                boardDiv.appendChild(cell);
            }
        }
        this.boardContainer.appendChild(boardDiv);

        // Update sequence counts
        const xSeq = board.countSequences('X');
        const oSeq = board.countSequences('O');
        document.getElementById('player1-score').textContent = `Sequences: ${xSeq}`;
        document.getElementById('player2-score').textContent = `Sequences: ${oSeq}`;
    }
}

function init5x5TTT(player1Config, player2Config) {
    const board = new FiveByFiveBoard();
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

    const ui = new FiveByFiveUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `
            <p><strong>5x5 Board:</strong> Count three-in-a-row sequences! Most sequences after 24 moves wins!</p>
        `;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.init5x5TTT = init5x5TTT;
}


