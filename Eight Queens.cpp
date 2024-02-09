#include <iostream>
using namespace std;
int board[8][8];
int step = 0;

void set_queen(int i, int j)
{
    for (int x = 0; x <= 7; x++)
    {
        board[x][j]++;
        board[i][x]++;
        int foo;
        foo = j - i + x;
        if (foo >= 0 && foo <= 7)
        {
            board[x][foo]++;
        }
        foo = i + j - x;
        if (foo >= 0 && foo <= 7)
        {
            board[x][foo]++;
        }
    }
    board[i][j] = -1;
    step++;
}

void reset_queen(int i, int j)
{
    for (int x = 0; x <= 7; x++)
    {
        board[x][j]--;
        board[i][x]--;
        int foo;
        foo = j - i + x;
        if (foo >= 0 && foo <= 7)
        {
            board[x][foo]--;
        }
        foo = i + j - x;
        if (foo >= 0 && foo <= 7)
        {
            board[x][foo]--;
        }
    }
    board[i][j] = 0;
}

bool try_queen(int i)
{
    bool result = false;
    for (int j = 0; j <= 7; j++)
    {
        if (board[i][j] == 0)
        {
            set_queen(i, j);
            if (i == 7)
            {
                result = true;
            }
            else
            {
                result = try_queen(i + 1);
                if (!result)
                {
                    reset_queen(i, j);
                }
            }
        }
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "rus");
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            board[i][j] = 0;
        }
    }
    try_queen(0);
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            if (board[i][j] == -1)
            {
                cout << "Ф";
            }
            else
            {
                cout << "[]";
            }
        }
        cout << '\n';
    }
    cout << "Потребовалось: " << step << " шагов";
    return 0;
}
