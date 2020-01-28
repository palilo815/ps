#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int T, n, x;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        scanf("%d", &n);
        set<int> st;
        set<int>::iterator it;
        while (n--) {
            scanf("%d", &x);
            it = st.find(x);
            if (it == st.end()) st.insert(x);
            else st.erase(it);
        }
        it = st.begin();
        printf("Case #%d: %d\n", i, *it);
    }
    return 0;
}