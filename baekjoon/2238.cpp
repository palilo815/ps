#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string name[100000];
int money[100000], cnt[10001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int U, N; cin >> U >> N;
    loop(i, N) {
        cin >> name[i] >> money[i];
        ++cnt[money[i]];
    }
    int num_p = INT32_MAX, idx;
    loop(i, U + 1)
        if (cnt[i] && cnt[i] < num_p) {
            num_p = cnt[i];
            idx = i;
        }
    loop(i, N)
        if (money[i] == idx) {
            cout << name[i] << ' ' << money[i];
            break;
        }
    return 0;
}