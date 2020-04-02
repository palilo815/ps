#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 50;
const int max_M = 10000;

int crane[max_N];
int cnt[max_N];
int box[max_M];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> crane[i];
    int M; cin >> M;
    loop(i, M) cin >> box[i];

    sort(crane, crane + N);
    sort(box, box + M);

    if (box[M - 1] > crane[N - 1]) {
        cout << -1;
        return 0;
    }

    int box_idx = 0;
    loop(i, N) {
        int tmp = 0;
        while (box_idx < M && box[box_idx] <= crane[i])
            ++box_idx, ++tmp;
        cnt[i] = tmp;
    }

    int ans = 0, sum = 0;
    for (int i = N - 1; i >= 0; --i) {
        sum += cnt[i];
        ans = max(ans, (sum - 1) / (N - i) + 1);
    }
    cout << ans;
    return 0;
}