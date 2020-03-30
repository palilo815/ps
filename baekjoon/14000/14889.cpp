#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int power[20][20];

int main() {
    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> power[i][j];

    vector<bool> select(N);
    loop(i, N / 2) select[i] = true;

    int ans = INT_MAX;
    do {
        int start = 0, link = 0;
        loop(i, N) loop(j, N)
            if (select[i] && select[j]) start += power[i][j];
            else if (!select[i] && !select[j]) link += power[i][j];
        ans = min(ans, abs(start - link));
    } while (prev_permutation(select.begin(), select.end()));
    cout << ans;
    return 0;
}