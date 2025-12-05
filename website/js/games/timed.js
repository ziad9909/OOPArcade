/**
 * timed.js
 * Timed/Infinity Tic Tac Toe - Replace pieces after 3 moves each
 */

class TimedBoard extends TicTacToeBoard {
    constructor() {
        super();
        this.moveHistory = [];
    }

    updateBoard(move) {
        const result = super.updateBoard(move);
        
        if (result) {
            this.moveHistory.push([move.getX(), move.getY(), move.getSymbol()]);

            // After 6 moves total (3 per player), start removing old pieces
            if (this.moveHistory.length > 6) {
                const oldMove = this.moveHistory.shift();
                this.board[oldMove[0]][oldMove[1]] = this.blankSymbol;
                this.nMoves--; // Keep board from filling up
            }
        }

        return result;
    }
}

class TimedUI extends TicTacToeUI {
    constructor() {
        super();
    }
}

function initTimedTTT(player1Config, player2Config) {
    const board = new TimedBoard();
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

    const ui = new TimedUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `
            <p><strong>Infinity Mode:</strong> Old pieces disappear after 3 moves! Keep adapting your strategy!</p>
        `;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.initTimedTTT = initTimedTTT;
}

