#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define eps 1e-8 // 유효 오차
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    map<string, int> mp;
    map<string, int>::iterator it;
    string s;
    int n;
    cin >> n;
    while (n-- > 0) {
        cin >> s;
        it = mp.find(s);
        if (it == mp.end())
            mp[s] = 1;
        else
            (*it).second++;
    }
    int best = 0;	// 가장 많이 팔린 권수
    string title;	// 가장 많이 팔린 책
    for (it = mp.begin(); it != mp.end(); ++it) {
        // 권수가 같으면 사전순
        if ((*it).second == best) {
            if ((*it).first < title) title = (*it).first;
        }
        // 더 많이 팔렸으면 update
        else if ((*it).second > best)
            best = (*it).second, title = (*it).first;
    }
    cout << title;
    return 0;
}