#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 2e4;
const int mxC = 10;

int a[mxN], diff[mxC];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];
    int C; cin >> C;
    loop(i, C) cin >> diff[i];

    sort(diff, diff + C);
    adjacent_difference(diff, diff + C, diff);

    vector<int> ans, song(C);
    loop(i, C) song[i] = a[i];

    for (int i = 0, j = C;; ++i, ++j) {
        sort(song.begin(), song.end());

        bool flag = true;
        for (int i = 1; i < C; ++i)
            if (song[i] - song[i - 1] != diff[i]) {
                flag = false;
                break;
            }
        if (flag) ans.emplace_back(i + 1);
        if (j == N) break;

        song.erase(find(song.begin(), song.end(), a[i]));
        song.emplace_back(a[j]);
    }

    cout << ans.size();
    for (int& x : ans)
        cout << '\n' << x;
    return 0;
}