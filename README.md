# OOP Game Arcade – Ultimate Tic-Tac-Toe Collection

A modern C++ object-oriented collection of **14 creative Tic-Tac-Toe variants + Connect Four**, built as a unified arcade with a clean menu system.

Perfect for learning OOP concepts: inheritance, polymorphism, templates, smart resource management, game loops, AI (random & minimax), and creative rule design.

---

### Games Included (14 + 1 Bonus)

| #  | Game                          | Board       | Win Condition                          | Unique Twist                              |
|----|-------------------------------|-------------|----------------------------------------|-------------------------------------------|
| 1  | Numerical Tic-Tac-Toe         | 3×3         | Line sums to 15 (odd vs even numbers)  | Magic square math game                    |
| 2  | Classic X-O                   | 3×3         | 3 in a row                             | The original                              |
| 3  | Misère Tic-Tac-Toe            | 3×3         | Force opponent to get 3 in a row       | Reverse logic                             |
| 4  | SUS                           | 3×3         | Most "SUS" sequences when board fills  | Meme scoring system                       |
| 5  | Word Tic-Tac-Toe              | 3×3         | Form valid 3-letter English word      | Dictionary-validated words                   |
| 6  | 4×4 Moving Tic-Tac-Toe        | 4×4         | 3 in a row by moving existing pieces   | No placing — only moving!                 |
| 7  | Obstacle 6×6 Tic-Tac-Toe      | 6×6         | 4 in a row                             | Random obstacles spawn every round         |
| 8  | Infinity (Timed) Tic-Tac-Toe  | 3×3         | 3 in a row                             | Oldest move disappears after every 3 turns|
| 9  | Four in a Row (Connect 4)     | 6×7         | 4 in a row (gravity)                   | Classic drop-disc game                    |
| 10 | Diamond Tic-Tac-Toe           | 5×5 diamond | 3-line AND 4-line in different dirs    | Dual complex win condition                 |
| 11 | 5×5 Tic-Tac-Toe               | 5×5         | Most 3-in-a-rows when board is full    | Score-based victory                       |
| 12 | Pyramid Tic-Tac-Toe           | Pyramid (6 cells) | 3 in special patterns            | Non-rectangular board                     |
| 13 | Memory Tic-Tac-Toe            | 3×3         | 3 in a row (board hidden until end)    | Fog of war — revealed only at game over   |
| 14 | Ultimate Tic-Tac-Toe          | 9× 3×3     | Win the meta 3×3 of local boards       | Game inside a game                        |

---

### Features

- Fully object-oriented design using templates (`Board<T>`, `Player<T>`, `Move<T>`, `UI<T>`)
- Polymorphic game manager works with `char`, `int`, custom types
- Clean separation: Board logic, UI, Player types, GameManager
- AI implementations:
  - Random players
  - Minimax with alpha-beta pruning (SUS, Connect 4, Diamond)
- Memory-safe with proper cleanup
- Beautiful console output for all variants (pyramid, diamond, ultimate, etc.)

---

### Project Structure
