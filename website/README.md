# 🎮 OOP Arcade - Board Games Collection

A complete web-based board games collection featuring 11 classic games, converted from C++ to JavaScript ES6 with beautiful UI and smart AI opponents.

## 🌟 Live Demo

Visit: [Your Netlify URL here after deployment]

## 📋 Features

### ✨ Games Included

1. **Classic Tic Tac Toe** - 3x3 grid with Minimax AI
2. **Four in a Row** (Connect 4) - 6x7 board with advanced Minimax AI and alpha-beta pruning
3. **Numerical Tic Tac Toe** - Use numbers 1-9, make lines sum to 15
4. **SUS Game** - Form "SUS" sequences, score-based gameplay with AI
5. **Misere Tic Tac Toe** - Reverse rules: avoid getting three in a row!
6. **Word Tic Tac Toe** - Form valid 3-letter English words
7. **4x4 Tic Tac Toe** - Expanded board with unique starting positions
8. **5x5 Tic Tac Toe** - Count three-in-a-row sequences, most wins after 24 moves
9. **Obstacle Tic Tac Toe** - 6x6 board with obstacles blocking your path
10. **Diamond Tic Tac Toe** - Play on a diamond-shaped board
11. **Timed Tic Tac Toe** - Infinity mode with disappearing pieces

### 🎯 Game Modes

- **👤 Human vs Human** - Play with a friend locally
- **🎲 Human vs Random AI** - Practice against random moves
- **🤖 Human vs Smart AI** - Challenge yourself against Minimax AI

### 💎 Key Features

- ✅ **Pure Vanilla JavaScript** - No frameworks or libraries
- ✅ **ES6 Class-Based Architecture** - Clean OOP design mirroring C++ structure
- ✅ **Responsive Design** - Works on desktop, tablet, and mobile
- ✅ **Beautiful Modern UI** - Dark theme with smooth animations
- ✅ **Smart AI Opponents** - Minimax algorithm with alpha-beta pruning
- ✅ **Live Score Tracking** - Real-time score updates for applicable games
- ✅ **Turn Indicators** - Clear visual feedback for current player
- ✅ **Winning Highlights** - Animated highlighting of winning combinations
- ✅ **No Backend Required** - 100% client-side application

## 📁 Project Structure

```
website/
├── index.html              # Home page with game selection
├── game.html              # Universal game page
├── css/
│   └── styles.css         # Complete styling with animations
├── js/
│   ├── base.js           # Core classes (Board, Player, Move, GameManager)
│   ├── main.js           # Game controller and initialization
│   ├── home.js           # Home page animations
│   └── games/            # Individual game implementations
│       ├── tictactoe.js  # Classic Tic Tac Toe + Minimax AI
│       ├── fourinarow.js # Four in a Row + Advanced AI
│       ├── numerical.js  # Numerical Tic Tac Toe
│       ├── sus.js        # SUS Game + Minimax AI
│       ├── misere.js     # Misere Tic Tac Toe
│       ├── word.js       # Word Tic Tac Toe
│       ├── 4x4.js        # 4x4 Tic Tac Toe
│       ├── 5x5.js        # 5x5 Tic Tac Toe
│       ├── obstacle.js   # Obstacle Tic Tac Toe
│       ├── diamond.js    # Diamond Tic Tac Toe
│       └── timed.js      # Timed Tic Tac Toe
└── README.md
```

## 🚀 Quick Start

### Local Development

1. **Clone or download this repository**
   ```bash
   cd website
   ```

2. **Open with a local server** (required for proper file loading)
   
   Using Python:
   ```bash
   # Python 3
   python -m http.server 8000
   
   # Python 2
   python -m SimpleHTTPServer 8000
   ```
   
   Using Node.js:
   ```bash
   npx http-server -p 8000
   ```
   
   Using PHP:
   ```bash
   php -S localhost:8000
   ```

3. **Open your browser**
   ```
   http://localhost:8000
   ```

### Direct File Opening (Alternative)

You can also open `index.html` directly in your browser, though using a local server is recommended for best compatibility.

## 🌐 Deployment

### Deploy to Netlify (Recommended)

1. **Create a Netlify account** at [netlify.com](https://www.netlify.com)

2. **Deploy via Drag & Drop:**
   - Go to [app.netlify.com/drop](https://app.netlify.com/drop)
   - Drag the entire `website` folder onto the page
   - Your site will be live in seconds!

3. **Deploy via Git (Recommended for updates):**
   ```bash
   # Initialize git repository (if not already)
   cd website
   git init
   git add .
   git commit -m "Initial commit"
   
   # Push to GitHub
   git remote add origin YOUR_GITHUB_REPO_URL
   git push -u origin main
   
   # Connect to Netlify:
   # - Go to netlify.com
   # - Click "New site from Git"
   # - Select your repository
   # - Build settings: Leave empty (static site)
   # - Publish directory: . (or leave empty)
   # - Click "Deploy site"
   ```

4. **Custom Domain (Optional):**
   - Go to Site settings → Domain management
   - Add your custom domain
   - Follow DNS configuration instructions

### Deploy to GitHub Pages

1. **Push to GitHub:**
   ```bash
   cd website
   git init
   git add .
   git commit -m "Initial commit"
   git branch -M main
   git remote add origin YOUR_GITHUB_REPO_URL
   git push -u origin main
   ```

2. **Enable GitHub Pages:**
   - Go to repository Settings → Pages
   - Source: Deploy from a branch
   - Branch: `main` → `/` (root)
   - Save

3. **Access your site:**
   ```
   https://YOUR_USERNAME.github.io/YOUR_REPO_NAME/
   ```

### Deploy to Vercel

1. **Install Vercel CLI:**
   ```bash
   npm install -g vercel
   ```

2. **Deploy:**
   ```bash
   cd website
   vercel
   ```

3. **Follow the prompts** and your site will be live!

## 🎮 How to Play

### General Instructions

1. **Select a Game** - Click on any game card from the home page
2. **Configure Players** - Set names and choose player types
3. **Start Game** - Click "Start Game" to begin
4. **Make Moves** - Click on cells to place your pieces
5. **Win Condition** - Each game has unique winning rules (displayed on screen)
6. **Restart** - Click the restart button to play again

### Game-Specific Rules

#### Classic Tic Tac Toe
- Get three in a row (horizontal, vertical, or diagonal)
- Standard 3x3 grid

#### Four in a Row (Connect 4)
- Drop pieces in columns to get four in a row
- 6 rows × 7 columns
- Pieces fall to the lowest available position

#### Numerical Tic Tac Toe
- Player 1 uses odd numbers (1, 3, 5, 7, 9)
- Player 2 uses even numbers (2, 4, 6, 8)
- Make any line sum to exactly 15 to win

#### SUS Game
- Player 1 places 'S', Player 2 places 'U'
- Form "SUS" sequences in any direction
- Highest score when board is full wins

#### Misere Tic Tac Toe
- **Reverse rules**: AVOID getting three in a row!
- Force your opponent to get three in a row

#### Word Tic Tac Toe
- Place letters to form valid 3-letter English words
- Words can be in rows, columns, or diagonals

#### 4x4 Tic Tac Toe
- Expanded 4×4 board
- Get 3 in a row to win

#### 5x5 Tic Tac Toe
- Count three-in-a-row sequences
- Game ends after 24 moves
- Player with most sequences wins

#### Obstacle Tic Tac Toe
- 6×6 board with obstacles
- Get 4 in a row to win
- Navigate around blocked cells

#### Diamond Tic Tac Toe
- Classic rules on a rotated board
- Visual twist on traditional gameplay

#### Timed Tic Tac Toe (Infinity Mode)
- Pieces disappear after 3 moves
- Keep adapting your strategy!

## 🏗️ Architecture

### Class Structure (Mirroring C++ Design)

```javascript
// Base Classes
- Board<T>              // Abstract board class
- Player<T>             // Base player class
- Move<T>               // Move representation
- GameManager<T>        // Game flow controller
- UI<T>                 // User interface base

// Player Types
- RandomAIPlayer        // Random move AI
- TicTacToeAIPlayer    // Minimax AI for Tic Tac Toe
- FourInARowAIPlayer   // Minimax AI for Connect 4
- SUSAIPlayer          // Minimax AI for SUS Game

// Game-Specific Boards
- TicTacToeBoard
- FourInARowBoard
- NumericalTTTBoard
- SUSBoard
- [etc...]
```

### Key Design Patterns

1. **Template Pattern** - Game flow management
2. **Strategy Pattern** - Different AI implementations
3. **Factory Pattern** - Player creation
4. **Observer Pattern** - UI updates

## 🤖 AI Implementation

### Minimax Algorithm

The smart AI uses the **Minimax algorithm with alpha-beta pruning** for optimal gameplay:

```javascript
// Minimax with Alpha-Beta Pruning
function minimax(depth, maximizing, aiSymbol, humanSymbol, alpha, beta) {
    // Base cases: terminal states
    if (isWin(ai)) return +10 - depth;
    if (isWin(human)) return -10 + depth;
    if (isDraw()) return 0;
    
    // Recursive exploration
    if (maximizing) {
        // AI's turn - maximize score
        for (each valid move) {
            score = minimax(depth+1, false, ...);
            alpha = max(alpha, score);
            if (beta <= alpha) break; // Pruning
        }
    } else {
        // Human's turn - minimize score
        for (each valid move) {
            score = minimax(depth+1, true, ...);
            beta = min(beta, score);
            if (beta <= alpha) break; // Pruning
        }
    }
}
```

### Heuristic Functions

For complex games like Four in a Row, we use sophisticated heuristics:

- **Sequence Counting** - Count 2, 3, 4 in a row
- **Position Value** - Center columns are worth more
- **Threat Detection** - Block opponent winning moves
- **Weighted Scoring** - Different weights for different patterns

## 🎨 Customization

### Changing Colors

Edit `css/styles.css` and modify CSS variables:

```css
:root {
    --primary-color: #6C63FF;    /* Change primary theme color */
    --secondary-color: #FF6584;   /* Change secondary color */
    --bg-color: #0F0F23;         /* Change background */
    --card-bg: #1a1a2e;          /* Change card background */
}
```

### Adding New Games

1. Create a new file in `js/games/yourgame.js`
2. Extend the `Board` class
3. Implement required methods: `updateBoard`, `isWin`, `isDraw`
4. Create a UI class extending `UI`
5. Create an init function
6. Add to `GAMES` object in `main.js`
7. Add a card to `index.html`

## 🔧 Browser Compatibility

- ✅ Chrome 90+
- ✅ Firefox 88+
- ✅ Safari 14+
- ✅ Edge 90+
- ✅ Opera 76+

## 📱 Mobile Support

Fully responsive design works on:
- 📱 Phones (320px+)
- 📱 Tablets (768px+)
- 💻 Desktops (1024px+)
- 🖥️ Large screens (1920px+)

## 🐛 Known Issues & Limitations

1. **Word Game Dictionary** - Limited to ~100 common words (can be expanded)
2. **AI Difficulty** - Fixed depth search (can be made configurable)
3. **No Undo Feature** - Currently not implemented
4. **No Game History** - Moves are not stored for replay

## 🚀 Future Enhancements

- [ ] Add multiplayer over network
- [ ] Save game state (localStorage)
- [ ] Game history and replay
- [ ] More comprehensive word dictionary
- [ ] Adjustable AI difficulty levels
- [ ] Sound effects and music
- [ ] Leaderboards and statistics
- [ ] More game variations

## 📄 License

This project is converted from an educational C++ project for demonstration purposes.
Feel free to use, modify, and distribute for learning and non-commercial purposes.

## 🙏 Acknowledgments

- Original C++ implementation from OOP course project
- Inspired by classic board games
- Reference site: https://boardgamestictactoe.netlify.app/

## 📧 Contact

For questions, suggestions, or issues, please open an issue on the repository.

---

**Built with ❤️ using pure HTML, CSS, and JavaScript ES6**

Enjoy playing! 🎮✨

