#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 10000;

int word[max_N];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    
    string s; int mask;
    loop(i, N) {
        mask = 0;
        cin >> s;
        for (char c : s) mask |= 1 << (c - 'a');
        word[i] = mask;
    }

    int remember = -1;
    int q; char c;
    while (Q--) {
        cin >> q >> c;
        if (q == 1) remember -= 1 << (c - 'a');
        else remember += 1 << (c - 'a');
        int cnt = 0;
        loop(i, N) if ((remember & word[i]) == word[i]) ++cnt;
        cout << cnt << '\n';
    }
    return 0;
}