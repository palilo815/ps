#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

P arr[1000];
bool cmp(P a, P b)
{
    return a.second > b.second;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, C; cin >> N >> C;
    int curr_size = 0;

    while (N--) {
        int x; cin >> x;
        loop(i, curr_size)
            if (arr[i].first == x) {
                ++arr[i].second;
                goto END;
            }
        arr[curr_size].first = x;
        arr[curr_size].second = 1;
        ++curr_size;
    END:;
    }

    stable_sort(arr, arr + curr_size, cmp);
    loop(i, curr_size) loop(j, arr[i].second)
        cout << arr[i].first << ' ';
    return 0;
}