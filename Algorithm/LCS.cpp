#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 100;
int DP[MAX + 1][MAX + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b; cin >> a >> b;
    int A = a.size(), B = b.size();
    loop(i, A) loop(j, B) {
        if (a[i] == b[j])
            DP[i + 1][j + 1] = DP[i][j] + 1;
        else if (DP[i][j + 1] > DP[i + 1][j])
            DP[i + 1][j + 1] = DP[i][j + 1];
        else
            DP[i + 1][j + 1] = DP[i + 1][j];
    }
    cout << DP[A][B] << '\n';

    stack<char> stk;
    int i = A, j = B;
    while (i && j) {
        if (a[i - 1] == b[j - 1]) {
            stk.push(a[i - 1]);
            --i, --j;
        }
        else if (DP[i - 1][j] > DP[i][j - 1])
            --i;
        else
            --j;
    }

    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
    return 0;
}