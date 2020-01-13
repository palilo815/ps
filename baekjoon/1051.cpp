#include<iostream>
#include<string>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, M, max = 1;
    cin >> N >> M;
    char** arr = new char* [N];

    for (int i = 0; i < N;i++)
        arr[i] = new char[M];
    for (int i = 0; i < N;i++)
        for (int j = 0;j < M;j++)
            cin >> arr[i][j];

    for (int i = 0;i < N;i++) {
        for (int j = 0; j < M - 1; j++) {
            for (int k = j + 1; k < M; k++) {
                if (arr[i][j] == arr[i][k]) {
                    int len = k - j + 1;
                    if (len <= max) continue;
                    char check = arr[i][j];
                    if (i + len - 1 < N)
                        if (arr[i + len - 1][j] == check && arr[i + len - 1][k] == check)
                            max = len;

                }
            }
        }
    }
    cout << max * max;

    return 0;
}