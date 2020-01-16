#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int max = 0, m_i, m_j, n;
    loop(i, 10) loop(j, 10) {
        cin >> n;
        if (n > max) {
            max = n;
            m_i = i + 1;
            m_j = j + 1;
        }
    }
    cout << max << '\n' << m_i << ' ' << m_j;
    return 0;
}