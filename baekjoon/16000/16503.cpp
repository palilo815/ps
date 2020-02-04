#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int solve(int a, int b, char op)
{
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        int tmp = 1;
        if (a < 0 && b >= 0) a = -a, tmp = -1;
        if (b < 0 && a >= 0) b = -b, tmp = -1;
        return a / b * tmp;
    }
}
int main()
{
    int num[3];
    char op[2];
    loop(i, 2) cin >> num[i] >> op[i];
    cin >> num[2];

    int ans1 = solve(num[0], num[1], op[0]);
    ans1 = solve(ans1, num[2], op[1]);
    int ans2 = solve(num[1], num[2], op[1]);
    ans2 = solve(num[0], ans2, op[0]);
    if (ans1 > ans2) swap(ans1, ans2);
    cout << ans1 << '\n' << ans2;
    return 0;
}