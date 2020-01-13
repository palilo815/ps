#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int tip[100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> tip[i];
    sort(tip, tip + n, greater<int>());
    long long Income = 0;
    loop(i, n) {
        long long tmp = tip[i] - i;
        if (tmp < 0) tmp = 0;
        Income += tmp;
    }
    cout << Income;
    return 0;
}