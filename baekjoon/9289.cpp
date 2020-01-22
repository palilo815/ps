#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string Code;
    string Decode[26] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
    
    int n; cin >> n;
    for (int T = 1; T <= n; ++T) {
        vector<char> Ans;
        loop(i, 5) {
            cin >> Code;
            char c;
            loop(j, 26)
                if (Decode[j] == Code) {
                    c = 'A' + j;
                    break;
                }
            Ans.push_back(c);
        }
        cout << "Case " << T << ": ";
        for (char c : Ans) cout << c;
        cout << '\n';
    }
    return 0;
}