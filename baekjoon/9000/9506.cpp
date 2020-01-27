#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

void perfect(int n)
{
    int sum = 0;
    vector<int> vt;
    for (int i = 1; i <= n / 2;i++) {
        if (n % i == 0) {
            sum += i;
            vt.push_back(i);
        }
    }
    if (sum == n) {
        cout << n << " = ";
        loop(i, vt.size()) {
            cout << vt[i];
            if (i != vt.size() - 1) cout << " + ";
            else cout << '\n';
        }
    }
    else
        cout << n << " is NOT perfect." << '\n';
}
int main()
{
    int n;
    while (1) {
        cin >> n;
        if (n == -1) break;
        perfect(n);
    }
    return 0;
}