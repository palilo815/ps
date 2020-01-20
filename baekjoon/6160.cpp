#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

struct cow {
    int num;
    int vote_1;
    int vote_2;
};
bool my_sort(cow& a, cow& b)
{
    return a.vote_1 > b.vote_1;
}
cow Cow[50000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    loop(i, n) {
        Cow[i].num = i + 1;
        cin >> Cow[i].vote_1 >> Cow[i].vote_2;
    }
    sort(Cow, Cow + n, my_sort);
    int MAX = 0, ans;
    loop(i, k)
        if (Cow[i].vote_2 > MAX) {
            ans = Cow[i].num;
            MAX = Cow[i].vote_2;
        }
    cout << ans;
    return 0;
}