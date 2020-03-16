#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1024;

int mat[max_N][max_N];

int max_222(int r, int c, int len) {
    if (len == 1) return mat[r][c];
    len /= 2;
    int arr[4];
    arr[0] = max_222(r, c, len);
    arr[1] = max_222(r, c + len, len);
    arr[2] = max_222(r + len, c, len);
    arr[3] = max_222(r + len, c + len, len);
    sort(arr, arr + 4);
    return arr[2];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];
    cout << max_222(0, 0, N);
    return 0;
}