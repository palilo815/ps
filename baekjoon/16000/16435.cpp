#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int fruit[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, L; cin >> N >> L;
    loop(i, N) cin >> fruit[i];
    sort(fruit, fruit + N);
    loop(i, N) {
        if (fruit[i] > L) break;
        ++L;
    }
    cout << L;
    return 0;
}