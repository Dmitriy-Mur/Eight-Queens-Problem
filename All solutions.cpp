#include <iostream>
#include <string>
using namespace std;

const int N = 8;         //При изменении этого значения мы можем найти решения для поля другого размера
int board[N][N] = { 0 }; // Инициализация шахматной доски (двумерный массив заполненный нулями)

void print_board();                                   //Функция для вывода решения на шахмотной доске в консоль
bool check_safety(int row, int col);                  //Функция для проверки, находится ли эта клетка под ударом 
void mark_under_attack(int row, int col, int val);    //Функция для отметки клеток, как находящихся под ударом
bool solve_searching(int col);                        //Функция для поиска решений

int main() {
    setlocale(LC_ALL, "Rus");
    if (!solve_searching(0)) {      //Когда решений задачи нет (2 или 3 ферзя) функция вернет false и мы пройдем по ветвлению
        cout << "Нет решений";
    }
    return 0;
}

void print_board() {
    static int solution_number = 0;
    cout << "Решение номер " << ++solution_number << ":\n";
    string s = "   A  B  C  D  E  F  G  H  I  J  K  L  M";
    for (int i = 0; i < N * 3 + 3; i++) {      // Подписываем столбцы буквами
        cout << s[i];
    }
    cout << "\n";
    for (int i = 0; i < N; ++i) {
        cout << i + 1 << " ";                  // Подписываем строки цифрами
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 1) {            //Встречая 1 выводим клетку с ферзем
                cout << "[Ф]";
            }
            else {                             //В остальных случаях выводим пустую клетку
                cout << "[ ]";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

bool check_safety(int row, int col) {
    //проверяем находится ли эта строка под боем(есть ли в ней ферзи)
    for (int i = 0; i < col; ++i) {
        if (board[row][i] == 1) {
            return false;
        }
    }

    //проверяем находится ли эта строка под боем(есть ли ферзи на этой диагонали слева сверху)
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    //проверяем находится ли эта строка под боем(есть ли ферзи на этой диагонали слева снизу)
    for (int i = row, j = col; i < N && j >= 0; ++i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    return true;
}

void mark_under_attack(int row, int col, int val) {
    int i, j; //Инициализируем заранее что бы не инециализировать затем в 6 циклах
    // Помечаем столбец (вертикаль)
    for (i = 0; i < N; ++i) {
        if (board[i][col] == 0) {
            board[i][col] = val;
        }
    }
    // Помечаем строку (горизонталь)
    for (j = 0; j < N; ++j) {
        if (board[row][j] == 0) {
            board[row][j] = val;
        }
    }
    // Помечаем диагонали
    // Идем от нашего ферзя влево вверх
    for (i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 0) {
            board[i][j] = val;
        }
    }
    // Идем от нашего ферзя вправо вниз
    for (i = row, j = col; i < N && j < N; ++i, ++j) {
        if (board[i][j] == 0) {
            board[i][j] = val;
        }
    }
    // Идем от нашего ферзя влево вверх
    for (i = row, j = col; i < N && j >= 0; ++i, --j) {
        if (board[i][j] == 0) {
            board[i][j] = val;
        }
    }
    // Идем от нашего ферзя вправо вниз
    for (i = row, j = col; i >= 0 && j < N; --i, ++j) {
        if (board[i][j] == 0) {
            board[i][j] = val;
        }
    }
}

bool solve_searching(int col) {
    if (col == N) {
        print_board();                      //Выводим решение в консоль
        return true;
    }
    bool res = false;                       // Переменная для отслеживания нахождения решения
    for (int i = 0; i < N; ++i) {
        if (check_safety(i, col)) {
            board[i][col] = 1;              //Ставим ферзя
            mark_under_attack(i, col, -1);  //Помечаем клетки находящиеся под ударом
            res = solve_searching(col + 1) || res;
            board[i][col] = 0;
            mark_under_attack(i, col, 0);   // Сбрасываем пометку клеток
        }
    }
    return res;
}
