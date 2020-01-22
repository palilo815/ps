#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string prev, curr;
    while (1) {
        cin >> prev;
        if (prev == "#") break;
        bool correct = true;
        while (1) {
            cin >> curr;
            if (curr == "#") break;
            if (correct) {
                if (prev.size() != curr.size()) correct = false;
                else {
                    int cnt = 0;
                    loop(i, prev.size())
                        if (prev[i] != curr[i]) ++cnt;
                    if (cnt != 1) correct = false;
                }
                prev = curr;
            }
        }
        if (correct) cout << "Correct\n";
        else cout << "Incorrect\n";
    }
    return 0;
}