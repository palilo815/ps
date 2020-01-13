#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    int** triangle = new int* [n];
    int** sum = new int* [n];
    for (int i = 0; i < n; i++) {
        triangle[i] = new int[i + 1];
        sum[i] = new int[i + 1];
        for (int j = 0; j < i + 1; j++)
            cin >> triangle[i][j];
    }
    sum[0][0] = triangle[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (j == 0) sum[i][j] = sum[i - 1][j] + triangle[i][j];
            else if (j == i) sum[i][j] = sum[i - 1][j - 1] + triangle[i][j];
            else sum[i][j] = max(sum[i - 1][j], sum[i - 1][j - 1]) + triangle[i][j];
        }
    }
    int max = sum[n - 1][0];
    for (int j = 0; j < n; j++)
        if (sum[n - 1][j] > max) max = sum[n - 1][j];
    cout << max;
    return 0;
}