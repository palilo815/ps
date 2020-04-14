#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

string arr[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    unordered_map<string, int> ump;
    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
        ump[arr[i]] = i + 1;
    }

    while (Q--) {
        string q; cin >> q;
        if (q[0] < 'A') {
            int idx = stoi(q);
            cout << arr[idx - 1];
        }
        else cout << ump.find(q)->second;
        cout << '\n';
    }
    return 0;
}