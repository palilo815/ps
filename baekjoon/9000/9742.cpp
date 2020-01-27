#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int fac(int n)
{
    if (n == 0 || n == 1) return 1;
    return n * fac(n - 1);
}

string kth(string& s, int k)
{
    if (k == 1) return s;
    int deg = fac(s.size() - 1);
    int i = (k - 1) / deg;
    char c = s[i];
    s.erase(s.begin() + i);
    return c + kth(s, k - i * deg);
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int k;
    while (cin >> s >> k) {
        int len = s.size();
        cout << s << ' ' << k << " = ";
        if (k > fac(len)) cout << "No permutation\n";
        else cout << kth(s, k) << '\n';
    }
    return 0;
}