#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // A진법 -> B진법
    int n, num = 0, A, B;
    cin >> A >> B >> n;
    while (n--) {
        int x; cin >> x;
        num += x * pow(A, n);
    }
    stack<int> stk;
    while (num) {
        stk.push(num % B);
        num /= B;
    }
    while (!stk.empty()) {
        cout << stk.top() << ' ';
        stk.pop();
    }
    return 0;
}