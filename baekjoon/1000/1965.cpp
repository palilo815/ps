#include<iostream>
#include<algorithm>
using namespace std;

int n;
int* box;
int* cache;

int maxLen(int start)
{
    int& ret = cache[start];
    if (ret != -1) return ret;

    ret = 1;
    for (int next = start + 1; next < n; next++)
        if (box[start] < box[next])
            ret = max(ret, maxLen(next) + 1);
    return ret;
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    cin >> n;
    box = new int[n];
    cache = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> box[i];
        cache[i] = -1;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, maxLen(i));
    cout << ans;
    return 0;
}