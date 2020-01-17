#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    string fbi = "FBI", s;
    vector<int> ans;
    loop(i, 5) {
        cin >> s;
        if (s.find(fbi) != string::npos)
            ans.push_back(i + 1);
    }
    if (ans.empty()) cout << "HE GOT AWAY!";
    else
        for (int x : ans) cout << x << ' ';
    return 0;
}