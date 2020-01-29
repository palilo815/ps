#include <bits/stdc++.h>
using namespace std;
const int max_N = 1000;

int abs_psum[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;

    int prev; cin >> prev;
    for (int i = 1;i < N;++i) {
        int curr; cin >> curr;
        abs_psum[i] = abs_psum[i - 1] + abs(curr - prev);
        prev = curr;
    }

    int a, b;
    while (Q--) {
        cin >> a >> b;
        cout << abs_psum[b - 1] - abs_psum[a - 1] << '\n';
    }
    return 0;
}