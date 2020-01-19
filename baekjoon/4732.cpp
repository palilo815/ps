#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string arr[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        getline(cin, s);
        if (s == "***") break;

        vector<int> vt;
        int len = s.size(), val;
        loop(i, len) {
            if (s[i] == ' ') {
                vt.push_back(val);
                while (i + 1 < len && s[i + 1] == ' ') ++i;
                continue;
            }
            switch (s[i]) {
            case 'A': val = 0; break;
            case 'B': val = 2; break;
            case 'C': val = 3; break;
            case 'D': val = 5; break;
            case 'E': val = 7; break;
            case 'F': val = 8; break;
            case 'G': val = 10; break;
            case '#': ++val; break;
            case 'b': --val;
            }
        }
        vt.push_back(val);

        getline(cin, s);
        int num = stoi(s);
        for (int x : vt) {
            x += num;
            if (x < 0) x += 12;
            else if (x > 11) x -= 12;
            cout << arr[x] << ' ';
        }
        cout << '\n';
    }
    return 0;
}