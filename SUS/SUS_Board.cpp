#include "SUS_Board.h"

// 1. الكونستركتور: نهيئ البورد 3x3 ونصفر النقاط
SUS_Board::SUS_Board() : Board<char>(3, 3) {
    p1_score = 0;
    p2_score = 0;
    // ملء البورد بمسافات فارغة لضمان عدم وجود قيم عشوائية
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' '; 
        }
    }
}

// 2. دالة لحساب عدد كلمات SUS المتكونة حول نقطة معينة
int SUS_Board::count_sus(int r, int c) {
    int points = 0;
    
    // تعريف المتجهات للاتجاهات الأربعة (أفقي، رأسي، قطرين)
    // dx, dy يمثلون التغير في الإحداثيات لفحص الجيران
    int dr[] = {0, 1, 1, 1}; 
    int dc[] = {1, 0, 1, -1};

    // نفحص الاتجاهات الأربعة
    // بما أن البورد 3x3 فقط، فإن أي كلمة SUS يجب أن تأخذ الصف أو العمود بالكامل
    
    // فحص الصف (Row) - هل الصف بالكامل S-U-S ؟
    if (board[r][0] == 'S' && board[r][1] == 'U' && board[r][2] == 'S') points++;

    // فحص العمود (Col) - هل العمود بالكامل S-U-S ؟
    if (board[0][c] == 'S' && board[1][c] == 'U' && board[2][c] == 'S') points++;

    // فحص القطر الرئيسي (فقط إذا كانت الخانة جزء منه)
    if (r == c) {
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') points++;
    }

    // فحص القطر العكسي (فقط إذا كانت الخانة جزء منه)
    if (r + c == 2) {
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') points++;
    }

    // ملاحظة: هذا المنطق بسيط ويعمل بدقة في بورد 3x3 
    // لأنك عندما تضع الحرف "الناقص" لتكملة الكلمة، تُحسب لك النقطة فوراً.
    return points;
}

// 3. تحديث البورد وتنفيذ الحركة
bool SUS_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol(); // اللاعب يختار S أو U

    // التحقق من صحة الحركة (داخل الحدود والمكان فارغ)
    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }

    // وضع الرمز في البورد
    board[r][c] = symbol;

    // حساب النقاط التي حققتها هذه الحركة
    int gained_points = count_sus(r, c);

    // معرفة دور من؟ (اللاعب 1 هو الحركات 0, 2, 4... واللاعب 2 هو 1, 3, 5...)
    if (n_moves % 2 == 0) {
        p1_score += gained_points;
    } else {
        p2_score += gained_points;
    }

    // زيادة عدد الحركات
    n_moves++;
    return true;
}

// 4. شرط انتهاء اللعبة: البورد مليان (9 حركات)
bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

// 5. شرط الفوز
// في هذه اللعبة، الفوز لا يحدث فجأة، بل ننتظر حتى الامتلاء ثم نقارن النقاط
bool SUS_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) return false; // اللعبة لم تنته بعد

    // بما أننا لا نملك طريقة مباشرة لمقارنة "player" الحالي بالنقاط داخل البورد
    // سنقوم بمقارنة النقاط فقط.
    // الـ Framework سينادي هذه الدالة ليعرف هل اللاعب الحالي فاز أم لا.
    // سنفترض هنا: إذا انتهت اللعبة والنقاط غير متساوية، فهناك فائز.
    // التحديد الدقيق لمن الفائز سيظهر عبر طباعة النقاط في الـ UI.
    return (p1_score != p2_score);
}

// 6. شرط التعادل
bool SUS_Board::is_draw(Player<char>* player) {
    // تعادل إذا انتهت اللعبة والنقاط متساوية
    return (game_is_over(player) && p1_score == p2_score);
}

// 7. الخسارة (عكس الفوز)
bool SUS_Board::is_lose(Player<char>* player) {
    return false;
}