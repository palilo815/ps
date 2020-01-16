#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    map<int, int> mp;
    int n, p, count = 1;
    cin >> n >> p;

    mp[n] = count;
    int tmp = n;
    while (1) {
        tmp = (tmp * n) % p;
        ++count;
        if (mp.find(tmp) == mp.end())
            mp[tmp] = count;
        else {
            cout << count - mp.find(tmp)->second;
            break;
        }
    }
    return 0;
}