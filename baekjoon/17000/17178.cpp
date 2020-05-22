#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 500;

string arr[M];
string ord[M];

bool cmp(string & a, string & b) {
    char A = a[0], B = b[0];
    return (A == B ? stoi(&a[2]) < stoi(&b[2]) : A < B);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    N *= 5;
    loop(i, N) cin >> arr[i];

    copy(arr, arr + N, ord);
    sort(ord, ord + N, cmp);

    stack<string> stk;
    int cur = 0, i = 0;
    for (int i = 0; i < N; ++i) {
        while (!stk.empty() && stk.top() == ord[cur])
            ++cur, stk.pop();
        if (arr[i] == ord[cur]) ++cur;
        else stk.emplace(arr[i]);
    }
    while (!stk.empty() && stk.top() == ord[cur])
        ++cur, stk.pop();

    cout << (stk.empty() ? "GOOD" : "BAD");
    return 0;
}