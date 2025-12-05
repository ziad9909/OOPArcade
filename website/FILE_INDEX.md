# 📑 File Index - Quick Reference

## 📂 Complete File List

### 📄 HTML Files (2)
```
index.html              # Home page with game selection cards
game.html               # Universal game page for all 11 games
```

### 🎨 CSS Files (1)
```
css/
└── styles.css          # Complete styling (~450 lines)
```

### ⚙️ JavaScript Core (3)
```
js/
├── base.js             # Core classes (Board, Player, Move, GameManager, UI)
├── main.js             # Game initialization and control
└── home.js             # Home page interactions
```

### 🎮 JavaScript Games (11)
```
js/games/
├── tictactoe.js        # Classic 3x3 + Minimax AI
├── fourinarow.js       # Connect 4 + Advanced AI
├── numerical.js        # Number-based Tic Tac Toe
├── sus.js              # SUS sequence game + AI
├── misere.js           # Reverse Tic Tac Toe
├── word.js             # Letter-based word game
├── 4x4.js              # 4x4 Tic Tac Toe
├── 5x5.js              # 5x5 sequence counting
├── obstacle.js         # 6x6 with obstacles
├── diamond.js          # Diamond-shaped board
└── timed.js            # Infinity mode
```

### 📚 Documentation (5)
```
README.md               # Main documentation (features, setup, games)
DEPLOYMENT.md           # Step-by-step deployment guide
BUILD_INSTRUCTIONS.md   # Local testing and development
PROJECT_SUMMARY.md      # Complete project overview
FILE_INDEX.md           # This file
```

---

## 🗂️ Directory Structure

```
website/
│
├── index.html              ← Start here!
├── game.html
│
├── css/
│   └── styles.css
│
├── js/
│   ├── base.js            ← Core classes
│   ├── main.js            ← Game controller
│   ├── home.js
│   │
│   └── games/
│       ├── tictactoe.js
│       ├── fourinarow.js
│       ├── numerical.js
│       ├── sus.js
│       ├── misere.js
│       ├── word.js
│       ├── 4x4.js
│       ├── 5x5.js
│       ├── obstacle.js
│       ├── diamond.js
│       └── timed.js
│
├── README.md              ← Read this first
├── DEPLOYMENT.md          ← How to deploy
├── BUILD_INSTRUCTIONS.md  ← How to test locally
├── PROJECT_SUMMARY.md     ← Project overview
└── FILE_INDEX.md          ← This file
```

---

## 🚀 Quick Start Guide

### 1️⃣ First Time? Read These
```
1. README.md               # Understand the project
2. BUILD_INSTRUCTIONS.md   # Set up local testing
3. DEPLOYMENT.md           # Publish your site
```

### 2️⃣ Want to Modify Code?
```
HTML:
- index.html              # Modify home page
- game.html               # Modify game page layout

CSS:
- css/styles.css          # Change colors, layout, animations

JavaScript Core:
- js/base.js              # Modify core game engine
- js/main.js              # Change game initialization

JavaScript Games:
- js/games/[game].js      # Modify specific game logic
```

### 3️⃣ Want to Add a New Game?
```
1. Create js/games/newgame.js
2. Extend Board class
3. Implement required methods
4. Create UI class
5. Add init function
6. Register in js/main.js
7. Add card to index.html
```

---

## 📋 File Purposes

### HTML Files
| File | Purpose | Size |
|------|---------|------|
| `index.html` | Home page with game grid | ~4 KB |
| `game.html` | Universal game page | ~3 KB |

### CSS Files
| File | Purpose | Size |
|------|---------|------|
| `styles.css` | All styling | ~12 KB |

### Core JS Files
| File | Purpose | Size | Lines |
|------|---------|------|-------|
| `base.js` | Core classes & utilities | ~10 KB | ~400 |
| `main.js` | Game controller | ~3 KB | ~150 |
| `home.js` | Home animations | ~2 KB | ~70 |

### Game JS Files
| File | Game | AI | Size | Lines |
|------|------|-------|------|-------|
| `tictactoe.js` | Classic 3x3 | Minimax | ~8 KB | ~280 |
| `fourinarow.js` | Connect 4 | Advanced | ~12 KB | ~420 |
| `numerical.js` | Numbers 1-9 | Random | ~8 KB | ~270 |
| `sus.js` | SUS sequences | Minimax | ~10 KB | ~340 |
| `misere.js` | Reverse rules | Random | ~2 KB | ~60 |
| `word.js` | Letter game | Random | ~6 KB | ~220 |
| `4x4.js` | 4x4 board | Random | ~4 KB | ~150 |
| `5x5.js` | Sequence count | Random | ~5 KB | ~180 |
| `obstacle.js` | With obstacles | Random | ~5 KB | ~170 |
| `diamond.js` | Rotated board | Random | ~3 KB | ~90 |
| `timed.js` | Infinity mode | Random | ~3 KB | ~100 |

### Documentation Files
| File | Purpose | Size | Lines |
|------|---------|------|-------|
| `README.md` | Main documentation | ~15 KB | ~450 |
| `DEPLOYMENT.md` | Deployment guide | ~12 KB | ~350 |
| `BUILD_INSTRUCTIONS.md` | Build guide | ~10 KB | ~320 |
| `PROJECT_SUMMARY.md` | Project overview | ~14 KB | ~400 |
| `FILE_INDEX.md` | This file | ~5 KB | ~230 |

---

## 🔍 Find What You Need

### "I want to..."

**...understand the project**
→ Read `README.md` and `PROJECT_SUMMARY.md`

**...test it locally**
→ Follow `BUILD_INSTRUCTIONS.md`

**...deploy it online**
→ Follow `DEPLOYMENT.md`

**...change colors**
→ Edit `css/styles.css` variables

**...modify a game**
→ Edit `js/games/[gamename].js`

**...add a new game**
→ See "Want to Add a New Game?" above

**...understand the code**
→ All files are well-commented

**...fix an issue**
→ Check `BUILD_INSTRUCTIONS.md` troubleshooting

---

## 📊 Project Statistics

- **Total Files:** 21
- **Total Size:** ~150 KB (uncompressed)
- **Total Lines:** ~3,500+
- **Languages:** HTML, CSS, JavaScript
- **Dependencies:** Zero (pure vanilla)
- **Games:** 11 fully playable
- **Documentation:** Comprehensive

---

## ✅ Checklist for Different Tasks

### 📝 Before First Use
- [ ] Read README.md
- [ ] Check file structure matches this index
- [ ] Verify all files present

### 🧪 Before Testing Locally
- [ ] Read BUILD_INSTRUCTIONS.md
- [ ] Start local server
- [ ] Open http://localhost:8000
- [ ] Test all 11 games

### 🚀 Before Deployment
- [ ] Test locally first
- [ ] Read DEPLOYMENT.md
- [ ] Choose deployment platform
- [ ] Follow platform-specific instructions

### 🔧 Before Modifying Code
- [ ] Understand file structure
- [ ] Read code comments
- [ ] Make backup copy
- [ ] Test changes locally

---

## 🎯 Quick Links

### Essential Files (Must Read)
1. `README.md` - Start here
2. `BUILD_INSTRUCTIONS.md` - Test locally
3. `DEPLOYMENT.md` - Go live

### Code Files (For Development)
1. `index.html` - Home page
2. `game.html` - Game page
3. `css/styles.css` - Styling
4. `js/base.js` - Core engine
5. `js/games/*.js` - Game logic

### Reference (For Understanding)
1. `PROJECT_SUMMARY.md` - Full overview
2. `FILE_INDEX.md` - This file

---

## 🎮 Games Quick Reference

| # | Game | File | Board | AI |
|---|------|------|-------|-----|
| 1 | Tic Tac Toe | `tictactoe.js` | 3×3 | ✅ Smart |
| 2 | Four in a Row | `fourinarow.js` | 6×7 | ✅ Smart |
| 3 | Numerical TTT | `numerical.js` | 3×3 | 🎲 Random |
| 4 | SUS Game | `sus.js` | 3×3 | ✅ Smart |
| 5 | Misere TTT | `misere.js` | 3×3 | 🎲 Random |
| 6 | Word TTT | `word.js` | 3×3 | 🎲 Random |
| 7 | 4×4 TTT | `4x4.js` | 4×4 | 🎲 Random |
| 8 | 5×5 TTT | `5x5.js` | 5×5 | 🎲 Random |
| 9 | Obstacle TTT | `obstacle.js` | 6×6 | 🎲 Random |
| 10 | Diamond TTT | `diamond.js` | 3×3 | 🎲 Random |
| 11 | Timed TTT | `timed.js` | 3×3 | 🎲 Random |

---

## 💡 Tips

### Finding Code
- Use Ctrl+F (Find) to search across files
- Game logic is in `js/games/`
- Core engine is in `js/base.js`
- Styling is in `css/styles.css`

### Understanding Flow
1. User opens `index.html`
2. Clicks game card → goes to `game.html?game=tictactoe`
3. `main.js` reads URL parameter
4. Loads appropriate game from `js/games/`
5. Game initializes board and players
6. `GameManager` handles turn flow
7. UI updates DOM on each move

### Making Changes
- **Small change:** Edit file, refresh browser
- **CSS change:** Might need hard refresh (Ctrl+Shift+R)
- **JS change:** Always hard refresh
- **HTML change:** Regular refresh is fine

---

## 🔗 Navigation

**Main Documentation:**
- [README.md](./README.md)
- [PROJECT_SUMMARY.md](./PROJECT_SUMMARY.md)

**Setup & Deployment:**
- [BUILD_INSTRUCTIONS.md](./BUILD_INSTRUCTIONS.md)
- [DEPLOYMENT.md](./DEPLOYMENT.md)

**File Reference:**
- [FILE_INDEX.md](./FILE_INDEX.md) ← You are here

---

**Last Updated:** December 5, 2025  
**Status:** ✅ Complete  
**Ready for:** 🚀 Deployment

---

*Need help? Check the troubleshooting sections in BUILD_INSTRUCTIONS.md*

