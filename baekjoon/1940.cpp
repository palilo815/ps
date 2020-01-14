#include<iostream>
#include<set>
#include<iterator>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m, ans = 0;
    set<int> st;
    cin >> n >> m;
    while (n--) {
        int x; cin >> x;
        auto it = st.find(m - x);
        if (it == st.end()) st.insert(x);
        else st.erase(it), ++ans;
    }
    cout << ans;
    return 0;
}