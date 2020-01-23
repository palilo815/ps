#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string s;
int Len;
bool sel[10];
int Lucky(int prev, int count)
{
    if (count == Len) return 1;
    int ret = 0;
    sel[prev] = true;
    char prevC = s[prev];
    set<char> Used;
    loop(i, Len) {
        char nextC = s[i];
        if (!sel[i] && prevC != nextC && Used.find(nextC) == Used.end()) {
            Used.insert(nextC);
            ret += Lucky(i, count + 1);
        }
    }
    sel[prev] = false;
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> s;
    Len = s.length();
    int Ans = 0;
    set<char> Used;
    loop(i, Len) {
        char c = s[i];
        if (Used.find(c) == Used.end()) {
            Used.insert(c);
            Ans += Lucky(i, 1);
        }
    }
    cout << Ans;
    return 0;
}