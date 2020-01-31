#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // i 증상이 걸리면 먹어야 하는 약
    // Yac[i] == -1 : 맞는 약이 없다. (사망)
    int Yac[101];
    memset(Yac, -1, sizeof(Yac));

    int N; cin >> N;
    while (N--) {
        int symp, num;
        cin >> symp >> num;
        Yac[symp] = num;
    }

    cin >> N;
    while (N--) {
        vector<int> vt;
        bool DIE = false;
        int m; cin >> m;
        while (m--) {
            int symp; cin >> symp;
            if (Yac[symp] == -1) DIE = true;
            if (!DIE) vt.push_back(Yac[symp]);
        }
        if (DIE) cout << "YOU DIED";
        else
            for (int x : vt)
                cout << x << ' ';
        cout << '\n';
    }
    return 0;
}