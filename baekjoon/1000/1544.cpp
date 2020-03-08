#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<string> st;
    string word;
    int N; cin >> N;
    while (N--) {
        cin >> word;
        int len = word.size();
        word += word;
        string tmp = "";
        for (int i = 0; i < len; ++i)
            tmp = max(tmp, word.substr(i, len));
        st.insert(tmp);
    }
    cout << st.size();
    return 0;
}