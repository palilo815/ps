#include<iostream>
using namespace std;
int main()
{
    char board[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            cin >> board[i][j];

    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < 8; j += 2) {
                if (board[i][j] == 'F')
                    count++;
            }
        }
        else {
            for (int j = 1; j < 8; j += 2)
                if (board[i][j] == 'F')
                    count++;
        }
    }
    cout << count;
    return 0;
}