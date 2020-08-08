#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    vector<int> vt;
    for (int x;;) {
        cin >> x;
        if (!x) break;
        vt.emplace_back(x);
    }
    sort(vt.begin(), vt.end());

    int N = vt.size();
    for (int i = 0; i < N - 2; ++i)
        if (vt[i] + vt[i + 1] > vt[i + 2]) {
            cout << vt[i] << ' ' << vt[i + 1] << ' ' << vt[i + 2];
            return 0;
        }
    cout << "NIE";
    return 0;
}