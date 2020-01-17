#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

bool sort_score(P& a, P& b)
{
    return a.first > b.first;
}
bool sort_idx(P& a, P& b)
{
    return a.second < b.second;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    P arr[8];
    loop(i, 8) {
        cin >> arr[i].first;
        arr[i].second = i + 1;
    }
    sort(arr, arr + 8, sort_score);
    sort(arr, arr + 5, sort_idx);
    
    int sum = 0;
    loop(i, 5) sum += arr[i].first;
    cout << sum << '\n';
    loop(i, 5) cout << arr[i].second << ' ';
    return 0;
}