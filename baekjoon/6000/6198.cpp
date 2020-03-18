#include <iostream>
using namespace std;
typedef unsigned int ui;

const int max_N = 80000;

int h[max_N];
int DP[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> h[i];

    // DP[i] : first index which is taller than i
    //         h[DP[i]] >= h[i]
    ui ans = 0;
    for (int i = N - 1; i >= 0; --i) {
        DP[i] = i + 1;
        while (DP[i] < N && h[i] > h[DP[i]])
            DP[i] = DP[DP[i]];
        ans += DP[i] - i - 1;
    }
    cout << ans;
    return 0;
}