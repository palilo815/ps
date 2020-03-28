#include <bits/stdc++.h>
using namespace std;

bool check[26];
int main() {
    int N, K; cin >> N >> K;
    vector<char> vt(N, '?');

    int n; char x;
    int it = 0;

    while (K--) {
        cin >> n >> x;
        it -= n;
        while (it < 0) it += N;
        if (vt[it] == '?') {
            if (check[x - 'A']) {
                cout << '!';
                return 0;
            }
            check[x - 'A'] = true;
            vt[it] = x;
        }
        else if (vt[it] != x) {
            cout << '!';
            return 0;
        }
    }

    int i = it;
    do {
        cout << vt[i];
        i = (i + 1) % N;
    } while (i != it);
    return 0;
}