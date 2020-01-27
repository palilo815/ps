#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 100000;

typedef struct {
    int age;
    string name;
}member;
bool cmp(member a, member b)
{
    return a.age < b.age;
}
member arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].age >> arr[i].name;
    stable_sort(arr, arr + N, cmp);
    loop(i, N) cout << arr[i].age << ' ' << arr[i].name << '\n';
    return 0;
}