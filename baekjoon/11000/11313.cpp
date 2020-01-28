#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

struct name {
    string F;
    string L;
};
name arr[99999];
int b_search(name& key, int s, int e)
{
    string key_F = key.F, key_L = key.L;
    while (1) {
        int m = s + (e - s) / 2;
        if (arr[m].L == key_L) {
            if (arr[m].F == key_F) return m;
            else if (arr[m].F > key_F) e = m;
            else s = m + 1;
        }
        else if (arr[m].L > key_L)
            e = m;
        else
            s = m + 1;
    }
}
bool my_sort(name& A, name& B)
{
    if (A.L == B.L) return A.F < B.F;
    else return A.L < B.L;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].F >> arr[i].L;
    sort(arr, arr + N, my_sort);

    int Q; cin >> Q;
    while (Q--) {
        name key;
        cin >> key.F >> key.L;
        int index = b_search(key, 0, N);
        int tmp = index;
        while (tmp % 3) --tmp;
        loop(i, 3) {
            if (tmp + i == index) continue;
            cout << arr[tmp + i].F << ' ' << arr[tmp + i].L << '\n';
        }
    }
    return 0;
}