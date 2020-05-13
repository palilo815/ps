#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int N;
int arr[11];
vector<int> vt;

stack<int> num;
stack<int> op;

void evaluate(int x) {
    int B = num.top(); num.pop();
    int A = num.top(); num.pop();
    switch (x) {
    case 0: num.emplace(A + B); break;
    case 1: num.emplace(A - B); break;
    case 2: num.emplace(A * B); break;
    case 3: num.emplace(A / B);
    }
}
int solve() {
    num.emplace(arr[0]);
    for (int i = 1; i < N; ++i) {
        switch (vt[i - 1]) {
        case 0:
        case 1:
            while (!op.empty())
                evaluate(op.top()), op.pop();
            op.emplace(vt[i - 1]);
            break;
        case 2:
        case 3:
            while (!op.empty() && op.top() >= 2)
                evaluate(op.top()), op.pop();
            op.emplace(vt[i - 1]);
        }
        num.emplace(arr[i]);
    }
    while (!op.empty())
        evaluate(op.top()), op.pop();

    int res = num.top(); num.pop();
    return res;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> arr[i];
    loop(i, 4) {
        int cnt; cin >> cnt;
        while (cnt--) vt.emplace_back(i);
    }

    int _max = INT_MIN, _min = INT_MAX;
    do {
        int res = solve();
        _max = max(res, _max);
        _min = min(res, _min);
    } while (next_permutation(vt.begin(), vt.end()));
    cout << _max << '\n' << _min;
    return 0;
}