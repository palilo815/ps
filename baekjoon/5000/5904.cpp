#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;

    stack<int> moo;
    moo.emplace(0);
    for (int i = 3;; ++i)
        if (moo.top() * 2 + i < N)
            moo.emplace(moo.top() * 2 + i);
        else break;

    for (int i = moo.size() + 2;; --i) {
        if (N > moo.top() + i) N -= moo.top() + i;
        else if (N > moo.top()) {N -= moo.top(); break;}
        moo.pop();
    }
    cout << (N == 1 ? 'm' : 'o');
    return 0;
}