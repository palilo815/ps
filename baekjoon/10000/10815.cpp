#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 500000;

int card[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N;
    loop(i, N) cin >> card[i];
    sort(card, card + N);
    cin >> M;
    while (M--) {
        int x; cin >> x;
        cout << binary_search(card, card + N, x) << ' ';
    }
    return 0;
}