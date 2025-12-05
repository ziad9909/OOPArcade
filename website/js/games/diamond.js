/**
 * diamond.js
 * Diamond-shaped Tic Tac Toe board
 */

class DiamondBoard extends TicTacToeBoard {
    constructor() {
        super();
        // Use standard 3x3 but display as diamond
    }
}

class DiamondUI extends TicTacToeUI {
    displayBoard(board) {
        this.boardContainer.innerHTML = '';
        const boardDiv = document.createElement('div');
        boardDiv.className = 'board size-3';
        boardDiv.style.transform = 'rotate(45deg)';
        boardDiv.style.margin = '80px auto';

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

                cell.style.transform = 'rotate(-45deg)';
                boardDiv.appendChild(cell);
            }
        }
        this.boardContainer.appendChild(boardDiv);
    }
}

function initDiamondTTT(player1Config, player2Config) {
    const board = new DiamondBoard();
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

    const ui = new DiamondUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `<p><strong>Diamond Shape:</strong> Classic rules on a rotated board!</p>`;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.initDiamondTTT = initDiamondTTT;
}

