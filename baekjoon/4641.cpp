#include<iostream>
#include<vector>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int x;
    while (1) {
        int ans = 0;
        vector<int> vt;
        while (1) {
            cin >> x;
            if (x == -1) return 0;
            else if (x == 0) break;
            else vt.push_back(x);
        }
        loop(i, vt.size()) {
            int key = vt[i] * 2;
            loop(j, vt.size())
                if (vt[j] == key) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}