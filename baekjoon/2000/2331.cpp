#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool visited[1000000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int prev, p;
    cin >> prev >> p;
    vector<int> vt;
    vt.push_back(prev);
    visited[prev] = true;

    while (1) {
        int curr = 0;
        while (prev) {
            curr += pow(prev % 10, p);
            prev /= 10;
        }

        if (visited[curr])
            loop(i, vt.size())
            if (vt[i] == curr) {
                cout << i;
                return 0;
            }
        visited[curr] = true;
        vt.push_back(curr);
        prev = curr;
    }
    return 0;
}