/**
 * word.js
 * Word Tic Tac Toe - Form valid 3-letter words to win
 * Simplified version with common word dictionary
 */

class WordTTTBoard extends Board {
    constructor() {
        super(3, 3);
        this.blankSymbol = '.';
        
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.columns; j++) {
                this.board[i][j] = this.blankSymbol;
            }
        }

        // Simple dictionary of common 3-letter words
        this.dictionary = new Set([
            'THE', 'AND', 'FOR', 'ARE', 'BUT', 'NOT', 'YOU', 'ALL', 'CAN', 'HER',
            'WAS', 'ONE', 'OUR', 'OUT', 'DAY', 'GET', 'HAS', 'HIM', 'HIS', 'HOW',
            'MAN', 'NEW', 'NOW', 'OLD', 'SEE', 'TWO', 'WAY', 'WHO', 'BOY', 'DID',
            'ITS', 'LET', 'PUT', 'SAY', 'SHE', 'TOO', 'USE', 'CAT', 'DOG', 'RUN',
            'SUN', 'FUN', 'CAR', 'BIG', 'BAD', 'HOT', 'EAT', 'FAT', 'RAT', 'BAT',
            'HAT', 'MAT', 'SAT', 'PAN', 'FAN', 'TAN', 'VAN', 'BAN', 'CAN', 'MAN',
            'ACE', 'AGE', 'AID', 'AIM', 'AIR', 'ART', 'AXE', 'BAG', 'BAR', 'BED',
            'BEE', 'BET', 'BIT', 'BOX', 'BUG', 'BUS', 'CAB', 'CUP', 'CUT', 'DAM'
        ]);
    }

    updateBoard(move) {
        const x = move.getX();
        const y = move.getY();
        const letter = move.getSymbol();

        if (x >= 0 && x < this.rows && y >= 0 && y < this.columns && 
            this.board[x][y] === this.blankSymbol) {
            this.board[x][y] = letter.toString().toUpperCase();
            this.nMoves++;
            return true;
        }
        return false;
    }

    isWin(player) {
        return this.checkForValidWord();
    }

    checkForValidWord() {
        // Check rows
        for (let i = 0; i < 3; i++) {
            if (this.board[i][0] !== '.' && this.board[i][1] !== '.' && this.board[i][2] !== '.') {
                const word = this.board[i][0] + this.board[i][1] + this.board[i][2];
                if (this.dictionary.has(word)) return true;
            }
        }

        // Check columns
        for (let j = 0; j < 3; j++) {
            if (this.board[0][j] !== '.' && this.board[1][j] !== '.' && this.board[2][j] !== '.') {
                const word = this.board[0][j] + this.board[1][j] + this.board[2][j];
                if (this.dictionary.has(word)) return true;
            }
        }

        // Check diagonals
        if (this.board[0][0] !== '.' && this.board[1][1] !== '.' && this.board[2][2] !== '.') {
            const word = this.board[0][0] + this.board[1][1] + this.board[2][2];
            if (this.dictionary.has(word)) return true;
        }

        if (this.board[0][2] !== '.' && this.board[1][1] !== '.' && this.board[2][0] !== '.') {
            const word = this.board[0][2] + this.board[1][1] + this.board[2][0];
            if (this.dictionary.has(word)) return true;
        }

        return false;
    }

    isDraw(player) {
        return this.nMoves === 9 && !this.isWin(player);
    }
}

class WordTTTUI extends UI {
    constructor() {
        super();
        this.selectedLetter = null;
    }

    displayBoard(board) {
        this.boardContainer.innerHTML = '';

        const container = document.createElement('div');
        container.style.display = 'flex';
        container.style.flexDirection = 'column';
        container.style.alignItems = 'center';
        container.style.gap = '20px';

        // Letter selection
        const letterSelection = document.createElement('div');
        letterSelection.id = 'letter-selection';
        letterSelection.style.display = 'flex';
        letterSelection.style.gap = '5px';
        letterSelection.style.flexWrap = 'wrap';
        letterSelection.style.justifyContent = 'center';
        letterSelection.style.padding = '15px';
        letterSelection.style.background = '#FFFFFF';
        letterSelection.style.border = '1px solid #E1E8ED';
        letterSelection.style.borderRadius = '12px';
        letterSelection.style.maxWidth = '600px';
        letterSelection.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.08)';

        'ABCDEFGHIJKLMNOPQRSTUVWXYZ'.split('').forEach(letter => {
            const btn = document.createElement('button');
            btn.textContent = letter;
            btn.style.width = '35px';
            btn.style.height = '35px';
            btn.style.fontSize = '1rem';
            btn.style.fontWeight = 'bold';
            btn.style.border = '1px solid #E1E8ED';
            btn.style.borderRadius = '5px';
            btn.style.background = '#FFFFFF';
            btn.style.color = '#2C3E50';
            btn.style.cursor = 'pointer';
            btn.style.transition = 'all 0.3s ease';
            btn.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.08)';

            if (this.selectedLetter === letter) {
                btn.style.borderColor = '#4DA6FF';
                btn.style.background = 'rgba(77, 166, 255, 0.15)';
                btn.style.boxShadow = '0 0 0 3px rgba(77, 166, 255, 0.1)';
            }

            btn.addEventListener('mouseenter', () => {
                btn.style.borderColor = '#4DA6FF';
                btn.style.boxShadow = '0 4px 12px rgba(0, 0, 0, 0.1)';
            });

            btn.addEventListener('mouseleave', () => {
                if (this.selectedLetter !== letter) {
                    btn.style.borderColor = '#E1E8ED';
                    btn.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.08)';
                }
            });

            btn.addEventListener('click', () => {
                this.selectedLetter = letter;
                this.displayBoard(board);
                this.clearMessage();
            });

            letterSelection.appendChild(btn);
        });

        container.appendChild(letterSelection);

        // Board
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
                            if (this.selectedLetter === null) {
                                this.displayMessage('Please select a letter first!', 'info');
                                return;
                            }

                            const move = new Move(row, col, this.selectedLetter);
                            if (window.gameManager.processMove(move)) {
                                this.selectedLetter = null;
                                this.displayBoard(board);
                            }
                        }
                    }
                });

                boardDiv.appendChild(cell);
            }
        }

        container.appendChild(boardDiv);
        this.boardContainer.appendChild(container);
    }

    updateTurnIndicator(player) {
        super.updateTurnIndicator(player);
        if (window.gameManager) {
            const board = window.gameManager.board;
            this.displayBoard(board);
        }
    }
}

function initWordTTT(player1Config, player2Config) {
    const board = new WordTTTBoard();
    const players = [];
    
    if (player1Config.type === 'human') {
        players.push(new Player(player1Config.name, 'P1', PlayerType.HUMAN));
    } else {
        players.push(new RandomAIPlayer(player1Config.name, 'P1'));
    }

    if (player2Config.type === 'human') {
        players.push(new Player(player2Config.name, 'P2', PlayerType.HUMAN));
    } else {
        players.push(new RandomAIPlayer(player2Config.name, 'P2'));
    }

    const ui = new WordTTTUI();
    const gameManager = new GameManager(board, players, ui);

    ui.displayBoard(board);
    ui.updateTurnIndicator(players[0]);

    document.querySelector('#player1-info .player-name').textContent = player1Config.name;
    document.querySelector('#player1-info .player-symbol').textContent = 'P1';
    document.querySelector('#player2-info .player-name').textContent = player2Config.name;
    document.querySelector('#player2-info .player-symbol').textContent = 'P2';

    const additionalInfo = document.getElementById('additional-info');
    if (additionalInfo) {
        additionalInfo.innerHTML = `
            <p><strong>How to play:</strong> Form a valid 3-letter English word in any row, column, or diagonal to win!</p>
        `;
    }

    if (players[0].getType() !== PlayerType.HUMAN) {
        setTimeout(() => gameManager.makeAIMove(), 500);
    }

    return gameManager;
}

if (typeof window !== 'undefined') {
    window.initWordTTT = initWordTTT;
}

