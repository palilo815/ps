#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;
typedef struct {
    int age;
    string name;
} member;

member arr[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].age >> arr[i].name;
    stable_sort(arr, arr + N, [](member a, member b) {return a.age < b.age;});
    loop(i, N) cout << arr[i].age << ' ' << arr[i].name << '\n';
    return 0;
}