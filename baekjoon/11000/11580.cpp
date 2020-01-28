#include <bits/stdc++.h>
#define P pair<int,int>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<P> st;
    int N, r = 0, c = 0;
    cin >> N;
    st.insert({ r,c });
    char x;
    while (N--) {
        cin >> x;
        if (x == 'N') ++r;
        else if (x == 'S') --r;
        else if (x == 'W') --c;
        else ++c;
        st.insert({ r,c });
    }
    cout << st.size();
    return 0;
}