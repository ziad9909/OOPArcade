#include "SUS.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

SUS_board::SUS_board() : Board<char>(3, 3) {
    srand(static_cast<unsigned int>(time(0)));
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    score_S = 0;
    score_U = 0;
}

// ✅ دالة جديدة: تفحص كم SUS sequence اكتملت بسبب الحركة الأخيرة
int SUS_board::check_new_sequences(int x, int y) {
    int count = 0;

    // Helper function للتحقق من SUS
    auto is_sus = [&](int r1, int c1, int r2, int c2, int r3, int c3) -> bool {
        return board[r1][c1] == 'S' && board[r2][c2] == 'U' && board[r3][c3] == 'S';
    };

    // 1️⃣ فحص الصف الأفقي (Horizontal)
    int row = x;
    for (int col = 0; col <= 0; col++) { // بس نفحص من 0 لأن عندنا 3 خانات بس
        if (is_sus(row, 0, row, 1, row, 2)) {
            // تأكد إن الحركة الحالية جزء من الـ SUS ده
            if (y >= 0 && y <= 2) {
                count++;
                break; // عشان منحسبش نفس الصف مرتين
            }
        }
    }

    // 2️⃣ فحص العمود الرأسي (Vertical)
    int col = y;
    for (int row = 0; row <= 0; row++) {
        if (is_sus(0, col, 1, col, 2, col)) {
            if (x >= 0 && x <= 2) {
                count++;
                break;
            }
        }
    }

    // 3️⃣ فحص القطر الرئيسي (Main Diagonal: top-left to bottom-right)
    if (x == y) { // الحركة على القطر الرئيسي
        if (is_sus(0, 0, 1, 1, 2, 2)) {
            count++;
        }
    }

    // 4️⃣ فحص القطر الثانوي (Anti-Diagonal: top-right to bottom-left)
    if (x + y == 2) { // الحركة على القطر الثانوي
        if (is_sus(0, 2, 1, 1, 2, 0)) {
            count++;
        }
    }

    return count;
}

bool SUS_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == blank_symbol) {
        board[x][y] = toupper(mark);
        n_moves++;

        // ✅ فحص كم SUS sequence اكتملت بالحركة دي
        int new_sequences = check_new_sequences(x, y);

        // ✅ إضافة النقاط للاعب اللي حط الحرف ده
        if (mark == 'S') {
            score_S += new_sequences;
        } else if (mark == 'U') {
            score_U += new_sequences;
        }

        // ✅ عرض النقاط الحالية بعد كل حركة
        if (new_sequences > 0) {
            cout << "\n " << mark << " completed " << new_sequences
                 << " SUS sequence(s)!\n";
        }
        cout << " Current Score: S = " << score_S << " | U = " << score_U << "\n";

        return true;
    }
    return false;
}

// ✅ تعديل get_score: نرجع النقاط المتراكمة مباشرة
int SUS_board::get_score(Player<char>* player) {
    char symbol = player->get_symbol();
    if (symbol == 'S') return score_S;
    if (symbol == 'U') return score_U;
    return 0;
}

bool SUS_board::is_win(Player<char>* player) {
    if(n_moves < 9) return false;

    char other = (player->get_symbol()=='S' ? 'U':'S');

    if (player->get_symbol() == 'S') {
        return score_S > score_U;
    } else {
        return score_U > score_S;
    }
}

bool SUS_board::is_lose(Player<char>* player) {
    if(n_moves < 9) return false;

    if (player->get_symbol() == 'S') {
        return score_S < score_U;
    } else {
        return score_U < score_S;
    }
}

bool SUS_board::is_draw(Player<char>* player) {
    if(n_moves < 9) return false;
    return score_S == score_U;
}

bool SUS_board::game_is_over(Player<char>* player) {
    return n_moves == 9;
}

// ------------------------------------------------------------
// AI IMPLEMENTATION (Updated)
// ------------------------------------------------------------

vector<pair<int,int>> SUS_board::get_empty_cells() {
    vector<pair<int,int>> v;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]=='.')
                v.push_back({i,j});
    return v;
}

// ✅ تعديل التقييم: نستخدم النقاط المتراكم
int SUS_board::evaluate_state(char aiSymbol) {
    if (aiSymbol == 'S') {
        return score_S - score_U;
    } else {
        return score_U - score_S;
    }
}

int SUS_board::minimax(int depth, bool maximizing, char aiSymbol, char humanSymbol, int alpha, int beta){
    if(depth==0 || n_moves==9)
        return evaluate_state(aiSymbol);

    vector<pair<int,int>> empty = get_empty_cells();

    if(maximizing){
        int best = -10000;
        for(auto &c: empty){
            // حفظ الحالة الحالية
            int old_score_S = score_S;
            int old_score_U = score_U;

            board[c.first][c.second] = aiSymbol;
            n_moves++;

            // تحديث النقاط
            int new_seq = check_new_sequences(c.first, c.second);
            if (aiSymbol == 'S') score_S += new_seq;
            else score_U += new_seq;

            best = max(best, minimax(depth-1,false,aiSymbol,humanSymbol,alpha,beta));

            // إرجاع الحالة
            board[c.first][c.second] = '.';
            n_moves--;
            score_S = old_score_S;
            score_U = old_score_U;

            alpha = max(alpha,best);
            if(beta <= alpha) break;
        }
        return best;
    }
    else{
        int best = 10000;
        for(auto &c: empty){
            // حفظ الحالة الحالية
            int old_score_S = score_S;
            int old_score_U = score_U;

            board[c.first][c.second] = humanSymbol;
            n_moves++;

            // تحديث النقاط
            int new_seq = check_new_sequences(c.first, c.second);
            if (humanSymbol == 'S') score_S += new_seq;
            else score_U += new_seq;

            best = min(best, minimax(depth-1,true,aiSymbol,humanSymbol,alpha,beta));

            // إرجاع الحالة
            board[c.first][c.second] = '.';
            n_moves--;
            score_S = old_score_S;
            score_U = old_score_U;

            beta = min(beta,best);
            if(beta<=alpha) break;
        }
        return best;
    }
}

pair<int,int> SUS_board::get_best_move(char aiSymbol, char humanSymbol){
    int bestValue = -10000;
    pair<int,int> bestMove = {-1,-1};

    vector<pair<int,int>> empty = get_empty_cells();
    for(auto &c: empty){
        // حفظ الحالة الحالية
        int old_score_S = score_S;
        int old_score_U = score_U;

        board[c.first][c.second] = aiSymbol;
        n_moves++;

        // تحديث النقاط
        int new_seq = check_new_sequences(c.first, c.second);
        if (aiSymbol == 'S') score_S += new_seq;
        else score_U += new_seq;

        int val = minimax(6,false,aiSymbol,humanSymbol,-10000,10000);

        // إرجاع الحالة
        board[c.first][c.second] = '.';
        n_moves--;
        score_S = old_score_S;
        score_U = old_score_U;

        if(val > bestValue){
            bestValue = val;
            bestMove = c;
        }
    }

    return bestMove;
}

// ------------------------------------------------------------
// Player UI
// ------------------------------------------------------------

SUS_player::SUS_player() : UI<char>("Welcome to SUS Game", 3) {
    srand(static_cast<unsigned int>(time(0)));
}

SUS_player::~SUS_player(){}

Player<char>* SUS_player::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** SUS_player::setup_players() {
    Player<char>** p = new Player<char>*[2];

    string n1 = get_player_name("Player 1");
    PlayerType t1 = get_player_type_choice("Player 1", {"Human","Computer"});
    p[0] = create_player(n1,'S',t1);

    string n2 = get_player_name("Player 2");
    PlayerType t2 = get_player_type_choice("Player 2", {"Human","Computer"});
    p[1] = create_player(n2,'U',t2);

    return p;
}

Move<char>* SUS_player::get_move(Player<char>* player) {
    Board<char>* board = player->get_board_ptr();
    char s = player->get_symbol();

    if(player->get_type() == PlayerType::HUMAN){
        int x,y;
        cout << "\n" << player->get_name() << " (" << s << ") enter move (row col): ";
        cin >> x >> y;

        return new Move<char>(x,y,s);
    }
    else{
        cout << "\nComputer is thinking...\n";

        char ai = s;
        char human = (s=='S' ? 'U':'S');

        auto mv = dynamic_cast<SUS_board*>(board)->get_best_move(ai,human);

        cout << "Computer played (" << mv.first << " , " << mv.second << ")\n";

        return new Move<char>(mv.first,mv.second,s);
    }
}