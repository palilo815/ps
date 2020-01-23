#include<iostream>
using namespace std;


int main()
{
    int paper[100][100] = {};
    int N, x, y;
    cin >> N;
    while (N-- > 0) {
        cin >> x >> y;
        for (int i = x;i < x + 10;i++)
            for (int j = y; j < y + 10;j++)
                paper[i][j] = 1;
    }
    int sum = 0;
    for (int i = 0; i < 100;i++)
        for (int j = 0;j < 100;j++)
            sum += paper[i][j];
    cout << sum;
    return 0;
}