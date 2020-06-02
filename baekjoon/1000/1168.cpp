#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    vector<int> vt(N);
    iota(vt.begin(), vt.end(), 1);

    --K;
    int i = K;
    cout << '<' << vt[i];
    vt.erase(vt.begin() + i);

    while (!vt.empty()) {
        i = (i + K) % vt.size();
        cout << ", " << vt[i];
        vt.erase(vt.begin() + i);
    }
    cout << '>';
    return 0;
}