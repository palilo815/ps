#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    string s; getline(cin, s);
    string Not[6] = { "Give you up", "Let you down", "Run around and desert you", "Make you cry", "Say goodbye", "Tell a lie and hurt you" };
    loop(i, 6) if (s == Not[i]) {
        cout << "NO";
        return 0;
    }
    cout << "YES";
    return 0;
}