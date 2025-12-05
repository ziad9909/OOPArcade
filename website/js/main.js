/**
 * main.js
 * Main game controller - handles game initialization and setup
 */

// Game configuration mapping
const GAMES = {
    'tictactoe': {
        name: 'Tic Tac Toe',
        init: initTicTacToe
    },
    'fourinarow': {
        name: 'Four in a Row',
        init: initFourInARow
    },
    'numerical': {
        name: 'Numerical Tic Tac Toe',
        init: initNumericalTTT
    },
    'sus': {
        name: 'SUS Game',
        init: initSUS
    },
    'misere': {
        name: 'Misere Tic Tac Toe',
        init: initMisereTTT
    },
    'word': {
        name: 'Word Tic Tac Toe',
        init: initWordTTT
    },
    '4x4': {
        name: '4x4 Tic Tac Toe',
        init: init4x4TTT
    },
    '5x5': {
        name: '5x5 Tic Tac Toe',
        init: init5x5TTT
    },
    'obstacle': {
        name: 'Obstacle Tic Tac Toe',
        init: initObstacleTTT
    },
    'diamond': {
        name: 'Diamond Tic Tac Toe',
        init: initDiamondTTT
    },
    'timed': {
        name: 'Timed Tic Tac Toe',
        init: initTimedTTT
    }
};

// Global game manager instance
window.gameManager = null;

// Current game type
let currentGameType = null;

// Player configurations
let player1Config = null;
let player2Config = null;

/**
 * Initialize the page on load
 */
document.addEventListener('DOMContentLoaded', () => {
    // Get game type from URL
    currentGameType = getURLParameter('game');

    if (!currentGameType || !GAMES[currentGameType]) {
        // Redirect to home if invalid game
        window.location.href = 'index.html';
        return;
    }

    // Set game title
    const gameTitle = document.getElementById('game-title');
    if (gameTitle) {
        gameTitle.textContent = GAMES[currentGameType].name;
    }

    // Setup event listeners
    setupEventListeners();
});

/**
 * Setup all event listeners
 */
function setupEventListeners() {
    // Start game button
    const startGameBtn = document.getElementById('start-game-btn');
    if (startGameBtn) {
        startGameBtn.addEventListener('click', startGame);
    }

    // Restart button
    const restartBtn = document.getElementById('restart-btn');
    if (restartBtn) {
        restartBtn.addEventListener('click', restartGame);
    }
}

/**
 * Start the game with selected configurations
 */
function startGame() {
    // Get player configurations
    const player1Name = document.getElementById('player1-name').value.trim() || 'Player 1';
    const player1Type = document.querySelector('input[name="player1-type"]:checked').value;

    const player2Name = document.getElementById('player2-name').value.trim() || 'Player 2';
    const player2Type = document.querySelector('input[name="player2-type"]:checked').value;

    player1Config = {
        name: player1Name,
        type: player1Type
    };

    player2Config = {
        name: player2Name,
        type: player2Type
    };

    // Hide setup section
    document.getElementById('setup-section').style.display = 'none';

    // Show game section
    document.getElementById('game-section').style.display = 'block';

    // Initialize the game
    initializeGame();
}

/**
 * Initialize the selected game
 */
function initializeGame() {
    if (!currentGameType || !GAMES[currentGameType]) {
        console.error('Invalid game type:', currentGameType);
        return;
    }

    try {
        // Call the game's initialization function
        const initFunction = GAMES[currentGameType].init;
        
        if (typeof initFunction !== 'function') {
            throw new Error(`Initialization function not found for ${currentGameType}`);
        }

        window.gameManager = initFunction(player1Config, player2Config);
        
        console.log(`${GAMES[currentGameType].name} initialized successfully!`);
    } catch (error) {
        console.error('Error initializing game:', error);
        alert('Error starting game. Please try again.');
        
        // Show setup again
        document.getElementById('setup-section').style.display = 'flex';
        document.getElementById('game-section').style.display = 'none';
    }
}

/**
 * Restart the current game
 */
function restartGame() {
    if (confirm('Are you sure you want to restart the game?')) {
        // Clear the game board
        const boardContainer = document.getElementById('board-container');
        if (boardContainer) {
            boardContainer.innerHTML = '';
        }

        // Clear messages
        const messageContainer = document.getElementById('game-message');
        if (messageContainer) {
            messageContainer.textContent = '';
            messageContainer.className = 'game-message';
        }

        // Reinitialize the game
        initializeGame();
    }
}

/**
 * Navigate back to home
 */
function goHome() {
    if (window.gameManager && !window.gameManager.isGameOver()) {
        if (confirm('Game in progress. Are you sure you want to leave?')) {
            window.location.href = 'index.html';
        }
    } else {
        window.location.href = 'index.html';
    }
}

// Expose utilities to window
window.startGame = startGame;
window.restartGame = restartGame;
window.goHome = goHome;

