#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define T tuple<int,int,int>

T arr[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) {
        int Country, Num, Score;
        cin >> Country >> Num >> Score;
        arr[i] = make_tuple(Score, Country, Num);
    }
    sort(arr, arr + n);

    int Ban = 0;
    if (get<1>(arr[n - 1]) == get<1>(arr[n - 2]))
        Ban = get<1>(arr[n - 1]);
    for (int i = n - 1; i >= n - 2; --i)
        cout << get<1>(arr[i]) << ' ' << get<2>(arr[i]) << '\n';
    for (int i = n - 3; i >= 0; --i)
        if (get<1>(arr[i]) != Ban) {
            cout << get<1>(arr[i]) << ' ' << get<2>(arr[i]);
            break;
        }
    return 0;
}