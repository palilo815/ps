#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 1000;

tup arr[max_N];
int DP[max_N][2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        auto& [x, y, c] = arr[i];
        cin >> x >> y >> c;
    }
    sort(arr, arr + N);

    // DP[i][0] : upward
    // DP[i][1] : downward
    loop(i, N) {
        auto [x, y, c] = arr[i];
        loop(j, i) {
            int Y = get<1>(arr[j]);
            if (Y < y) DP[i][0] = max(DP[i][0], DP[j][0]);
            else DP[i][1] = max(DP[i][1], DP[j][1]);
        }
        DP[i][0] += c, DP[i][1] += c;
    }
    cout << *max_element(&DP[0][0], &DP[N][0]);
    return 0;
}