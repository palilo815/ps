#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

int h[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> h[i];
    sort(h, h + N);

    // N개 전부 하나씩 제거하는 경우
    int ans = N;
    loop(i, N) {
        // h[i] 높이만큼 제거하고, 나머지는 일일히 제거
        while (i + 1 < N && h[i] == h[i + 1]) ++i;
        ans = min(ans, h[i] + N - i - 1);
    }
    cout << ans;
    return 0;
}