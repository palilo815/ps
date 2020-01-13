#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    map<string, int> mp;
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        auto it = mp.find(s);
        if (it == mp.end())
            mp[s] = 1;
        else
            it->second++;
    }
    string ans_name;
    int ans_num = 0;
    for (auto it : mp)
        if (it.second >= ans_num) {
            ans_num = it.second;
            ans_name = it.first;
        }
    cout << ans_name << ' ' << ans_num;
    return 0;
}