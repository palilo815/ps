#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

void MinusYee(int n)
{
    if (n == 0) {
        cout << n;
        return;
    }
    stack<int> stk;
    while (n) {
        if (n % (-2) == -1) {
            stk.push(1);
            n = n / (-2) + 1;
        }
        else {
            stk.push(n % (-2));
            n /= (-2);
        }
    }
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    MinusYee(n);
    return 0;
}