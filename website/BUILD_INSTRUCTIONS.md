# 🔨 Build Instructions - OOP Arcade

## 📁 Folder Structure

Your website folder should contain:

```
website/
│
├── index.html              # Home page
├── game.html              # Game page
│
├── css/
│   └── styles.css         # All styles
│
├── js/
│   ├── base.js           # Core classes
│   ├── main.js           # Game controller
│   ├── home.js           # Home page logic
│   │
│   └── games/            # Game implementations
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
├── README.md
├── DEPLOYMENT.md
└── BUILD_INSTRUCTIONS.md  # This file
```

## 🚀 Quick Start (3 Steps)

### Step 1: Verify Files

Make sure all files are present. Check:

```bash
cd website
ls -la
```

You should see: `index.html`, `game.html`, `css/`, `js/`

### Step 2: Start Local Server

Choose one of these methods:

#### Option A: Python (Recommended)

```bash
# Python 3.x
python -m http.server 8000

# Python 2.x
python -m SimpleHTTPServer 8000
```

#### Option B: Node.js

```bash
# Install http-server globally (one time)
npm install -g http-server

# Run server
http-server -p 8000
```

#### Option C: PHP

```bash
php -S localhost:8000
```

#### Option D: VS Code Live Server

1. Install "Live Server" extension in VS Code
2. Right-click `index.html`
3. Select "Open with Live Server"

### Step 3: Open in Browser

Visit: `http://localhost:8000`

## 🎮 Testing Checklist

### ✅ Home Page
- [ ] All 11 game cards are displayed
- [ ] Hover effects work on cards
- [ ] Click on each card navigates to game page

### ✅ Game Setup
- [ ] Player names can be entered
- [ ] Player type selection (Human/Random/Smart) works
- [ ] Start button launches the game

### ✅ Each Game
Test all 11 games individually:

1. **Tic Tac Toe**
   - [ ] 3x3 board displays correctly
   - [ ] Cells are clickable
   - [ ] Win detection works (row, column, diagonal)
   - [ ] Draw detection works
   - [ ] Smart AI makes reasonable moves

2. **Four in a Row**
   - [ ] 6x7 board displays
   - [ ] Pieces drop to bottom
   - [ ] Hover effect shows column
   - [ ] Win detection (4 in a row)
   - [ ] Smart AI is challenging

3. **Numerical Tic Tac Toe**
   - [ ] Number selection appears
   - [ ] Odd numbers for Player 1
   - [ ] Even numbers for Player 2
   - [ ] Win on sum = 15 works

4. **SUS Game**
   - [ ] Score tracking displays
   - [ ] SUS sequence detection works
   - [ ] Final score comparison correct

5. **Misere Tic Tac Toe**
   - [ ] Reverse win condition works
   - [ ] Player who gets 3-in-a-row loses

6. **Word Tic Tac Toe**
   - [ ] Letter selection keyboard works
   - [ ] Valid word detection works
   - [ ] At least some common words recognized

7. **4x4 Tic Tac Toe**
   - [ ] 4x4 board displays
   - [ ] Starting pieces in place
   - [ ] 3-in-a-row win condition

8. **5x5 Tic Tac Toe**
   - [ ] 5x5 board displays
   - [ ] Sequence counting displays
   - [ ] Game ends after 24 moves
   - [ ] Correct winner determined

9. **Obstacle Tic Tac Toe**
   - [ ] 6x6 board with obstacles
   - [ ] Obstacles prevent placement
   - [ ] 4-in-a-row win detection

10. **Diamond Tic Tac Toe**
    - [ ] Board appears rotated
    - [ ] Regular rules apply
    - [ ] Visual effect is clear

11. **Timed Tic Tac Toe**
    - [ ] Pieces disappear after moves
    - [ ] Only recent 3 pieces per player show
    - [ ] Game continues indefinitely

### ✅ Game Controls
- [ ] Restart button works
- [ ] Back to home button works
- [ ] Turn indicator updates correctly

### ✅ Responsive Design
Test on different screen sizes:
- [ ] Mobile (375px width)
- [ ] Tablet (768px width)
- [ ] Desktop (1920px width)

### ✅ Browser Compatibility
- [ ] Chrome
- [ ] Firefox
- [ ] Safari
- [ ] Edge

## 🐛 Common Issues & Fixes

### Issue: "Failed to load resource"

**Cause:** Files are missing or paths are incorrect

**Fix:**
1. Check file structure matches above
2. Verify all files exist
3. Check file names for typos
4. Ensure paths use forward slashes `/`

### Issue: Games don't initialize

**Cause:** JavaScript loading order is wrong

**Fix:**
1. `base.js` must load first
2. All game files must load before `main.js`
3. Check `game.html` script order

### Issue: Styles not applying

**Cause:** CSS file not found or cached

**Fix:**
1. Clear browser cache (Ctrl+Shift+R)
2. Check `css/styles.css` exists
3. Verify path in HTML `<link>` tag

### Issue: AI not working

**Cause:** Game class not defined or error in AI logic

**Fix:**
1. Open browser console (F12)
2. Look for JavaScript errors
3. Verify specific game file is loaded
4. Check for syntax errors

### Issue: Blank page

**Cause:** JavaScript error preventing page load

**Fix:**
1. Open browser console
2. Check for error messages
3. Fix any syntax errors
4. Reload page

## 📊 Performance Testing

### Check Load Time
1. Open browser DevTools (F12)
2. Go to Network tab
3. Reload page
4. Check total load time (should be < 1 second)

### Check for Errors
1. Open Console tab
2. Look for red error messages
3. Fix any errors found

### Memory Usage
1. Open Performance tab
2. Record while playing a game
3. Check for memory leaks (shouldn't grow continuously)

## 🔧 Development Tips

### Making Changes

1. **CSS Changes:**
   - Edit `css/styles.css`
   - Refresh browser (Ctrl+R)
   - Clear cache if needed (Ctrl+Shift+R)

2. **JavaScript Changes:**
   - Edit relevant JS file
   - Hard refresh browser (Ctrl+Shift+R)
   - Check console for errors

3. **HTML Changes:**
   - Edit HTML file
   - Refresh browser (Ctrl+R)

### Debugging

**Chrome DevTools:**
```
F12 - Open DevTools
Ctrl+Shift+C - Inspect element
Ctrl+Shift+J - Console
```

**Add Debug Logs:**
```javascript
console.log('Debug:', variable);
console.error('Error:', error);
console.table(array);
```

**Breakpoints:**
1. Open DevTools → Sources
2. Find your JS file
3. Click line number to add breakpoint
4. Trigger code execution
5. Step through code

## 📝 Code Quality

### Check for Console Errors

Run each game and check:
```javascript
// Should see no errors
// Console should be clean
```

### Validate HTML

Use [W3C Validator](https://validator.w3.org/):
- Upload `index.html` and `game.html`
- Fix any errors

### Validate CSS

Use [W3C CSS Validator](https://jigsaw.w3.org/css-validator/):
- Upload `styles.css`
- Fix any errors

## 🎨 Customization

### Change Theme Colors

Edit `css/styles.css`:

```css
:root {
    --primary-color: #6C63FF;    /* Your color here */
    --secondary-color: #FF6584;
    --bg-color: #0F0F23;
}
```

### Add New Game

1. Create `js/games/newgame.js`
2. Define board class extending `Board`
3. Implement required methods
4. Create UI class
5. Add init function
6. Register in `main.js` GAMES object
7. Add card to `index.html`

### Modify Game Rules

Edit specific game file in `js/games/`:
- `isWin()` - Win condition
- `isDraw()` - Draw condition
- `updateBoard()` - Move logic

## ✅ Pre-Deployment Checklist

- [ ] All games tested
- [ ] No console errors
- [ ] HTML/CSS validated
- [ ] Responsive design works
- [ ] All links work
- [ ] README updated
- [ ] Files organized correctly

## 🚀 Ready to Deploy!

Once all tests pass, follow [DEPLOYMENT.md](./DEPLOYMENT.md) for publishing instructions.

---

## 📞 Need Help?

1. Check browser console for errors
2. Verify file structure
3. Try different browser
4. Clear cache and reload

**Happy Building! 🎮**

