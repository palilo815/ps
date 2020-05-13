#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 12;

int ball[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> ball[i];
    sort(ball, ball + N);

    int T; cin >> T;
    T *= 2;

    int ans = 0;
    loop(dir, 1 << N) loop(i, N) if (dir & (1 << i))
        for (int j = i + 1; j < N && ball[j] - ball[i] <= T; ++j)
            if (!(dir & (1 << j)))
                ++ans;
    cout << fixed << setprecision(10)
         << 1.0 * ans / (1 << N);
    return 0;
}