#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<string> st;
    string name, log;
    int n; cin >> n;
    while (n--) {
        cin >> name >> log;
        if (log == "enter") st.insert(name);
        else st.erase(name);
    }
    for (auto it = st.rbegin(); it != st.rend();++it)
        cout << *it << '\n';
    return 0;
}