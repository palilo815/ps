#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 500000;

char num[max_N];
char r_max[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    loop(i, N) cin >> num[i];
    for (int i = N - 1; i > 0; --i)
        r_max[i - 1] = max(num[i], r_max[i]);

    string ans;
    loop(i, N) {
        if (num[i] < r_max[i] && K) --K;
        else ans += num[i];
    }
    N = ans.size();
    loop(i, N - K) cout << ans[i];
    return 0;
}