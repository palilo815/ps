#include<iostream>
#include<set>
#include<iterator>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s;
    set<string>::iterator it;
    set<string> NoHear;
    set<string> ans;
    int n, m;
    cin >> n >> m;
    while (n-- > 0) {
        cin >> s;
        NoHear.insert(s);
    }
    while (m-- > 0) {
        cin >> s;
        it = NoHear.find(s);
        if (it != NoHear.end())
            ans.insert(*it);
    }
    cout << ans.size() << '\n';
    for (it = ans.begin();it != ans.end();it++)
        cout << *it << '\n';
    return 0;
}