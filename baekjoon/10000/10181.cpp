#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (n == -1) break;
        vector<int> DIV;
        int sum = 0;
        for (int i = 1; i <= n / 2;++i)
            if (n % i == 0) {
                sum += i;
                DIV.push_back(i);
            }
        cout << n;
        if (sum == n)
            loop(i, DIV.size()) {
            if (i) cout << " + ";
            else cout << " = ";
            cout << DIV[i];
        }
        else cout << " is NOT perfect.";
        cout << '\n';
    }
    return 0;
}