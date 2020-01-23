#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 이름이 홀수번 나오는 사람을 고르면 된다.
    set<string> st;
    int N; cin >> N;
    N = 2 * N - 1;
    while (N--) {
        string name; cin >> name;
        auto it = st.find(name);
        if (it == st.end())
            st.insert(name);
        else
            st.erase(name);
    }
    cout << *(st.begin());
    return 0;
}