#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
#define MOD 1000000000

// 소인수분해해서 집어넣는다.
void add_div(int count, vector<int>& vt)
{
    int num;
    while (count--) {
        cin >> num;
        while (num % 2 == 0) {
            num /= 2;
            vt.push_back(2);
        }
        for (int i = 3; i * i <= num; i += 2)
            while (num % i == 0) {
                num /= i;
                vt.push_back(i);
            }
        if (num != 1) vt.push_back(num);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m;
    vector<int> vt1, vt2;
    cin >> n;
    add_div(n, vt1);
    cin >> m;
    add_div(m, vt2);
    sort(vt1.begin(), vt1.end());
    sort(vt2.begin(), vt2.end());

    auto p1 = vt1.begin(), p2 = vt2.begin();
    ll ans = 1;
    bool overflow = false;
    while (p1 != vt1.end() && p2 != vt2.end()) {
        if (*p1 == *p2) {
            ans = ans * (ll)(*p1);
            if (ans >= MOD) {
                ans %= MOD;
                overflow = true;
            }
            ++p1, ++p2;
        }
        else if (*p1 < *p2)	++p1;
        else ++p2;
    }

    if (overflow)
        cout << setfill('0') << setw(9) << ans;
    else
        cout << ans;
    return 0;
}