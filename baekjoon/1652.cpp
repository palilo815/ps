#include<iostream>
using namespace std;

int main()
{
    int N, Garo = 0, Sero = 0;
    cin >> N;
    char** room = new char* [N];
    for (int i = 0; i < N; i++)
        room[i] = new char[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> room[i][j];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (room[i][j] == '.' && room[i][j + 1] == '.') {
                Garo++;
                while (room[i][j] == '.' && j < N - 1) j++;
            }
        }
    }
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N - 1; i++) {
            if (room[i][j] == '.' && room[i + 1][j] == '.') {
                Sero++;
                while (room[i][j] == '.' && i < N - 1) i++;
            }
        }
    }
    cout << Garo << " " << Sero;
    return 0;
}