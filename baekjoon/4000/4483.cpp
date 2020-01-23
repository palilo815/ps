#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string name[25];
bool pres[25];
void check(const string& s, int N)
{
    loop(i, N)
        if (name[i] == s) {
            pres[i] = true;
            return;
        }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N, L;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        memset(pres, 0, sizeof(pres));
        cin >> N;
        loop(i, N) cin >> name[i];
        cin >> L; cin.ignore();
        while (L--) {
            string s; getline(cin, s);
            int len = s.size(), prev = 0;
            loop(curr, len)
                if (s[curr] == ' ') {
                    check(s.substr(prev, curr - prev), N);
                    prev = curr + 1;
                }
            check(s.substr(prev, len - prev), N);
        }
        cout << "Test set " << t << ":\n";
        loop(i, N) {
            cout << name[i] << " is ";
            if (pres[i]) cout << "present\n";
            else cout << "absent\n";
        }
        cout << '\n';
    }
    return 0;
}