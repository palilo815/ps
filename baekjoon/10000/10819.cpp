#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int ans, n, arr[8];
bool selected[8];
void Brute(int curr, int count, int Sum)
{
    if (count == n) { ans = max(ans, Sum);return; }
    selected[curr] = true;
    int val = arr[curr];
    loop(i, n)
        if (!selected[i])
            Brute(i, count + 1, Sum + abs(arr[i] - val));
    selected[curr] = false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ans = INT_MIN;
    cin >> n;
    loop(i, n) cin >> arr[i];
    loop(i, n) Brute(i, 1, 0);
    cout << ans;
    return 0;
}