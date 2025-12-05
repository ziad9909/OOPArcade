/**
 * misere.js
 * Misere Tic Tac Toe - Reverse rules: AVOID getting three in a row!
 * Converted from C++ Misere_TTT_Classes.cpp
 */

class MisereTTTBoard extends TicTacToeBoard {
    constructor() {
        super();
        // Reuse TicTacToeBoard but reverse win/lose logic
    }

    /**
     * In Misere, getting three in a row means you LOSE
     * @param {Player} player
     * @returns {boolean}
     */
    isLose(player) {
        // Check if player got three in a row (which is bad in Misere!)
        return super.isWin(player);
    }

    /**
     * No traditional "win" in Misere - you win if opponent gets three in a row
     * @param {Player} player
     * @returns {boolean}
     */
    isWin(player) {
        return false; // Handled by opponent's isLose
    }

    /**
     * Draw if board is full and nobody got three in a row
     * @param {Player} player
     * @returns {boolean}
     */
    isDraw(player) {
        return this.nMoves === 9 && !this.isLose(player);
    }
}

class MisereTTTUI extends TicTacToeUI {
    constructor() {
        super();
    }
}

function initMisereTTT(player1Config, player2Config) {
    const board = new MisereTTTBoard();
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

    const ui = new MisereTTTUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `
            <p><strong>Reverse Rules:</strong> AVOID getting three in a row! Force your opponent to get three!</p>
        `;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.initMisereTTT = initMisereTTT;
}

