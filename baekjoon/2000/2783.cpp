#include <bits/stdc++.h>
using namespace std;

int main()
{
    double N, ans, won, per_gram;
    cin >> won >> per_gram;
    ans = won / per_gram;
    cin >> N;
    while (N--) {
        cin >> won >> per_gram;
        ans = min(ans, won / per_gram);
    }
    cout << ans * 1000;
    return 0;
}