#include<iostream>
#include<algorithm>
using namespace std;

const int max_N = 20000;

string arr[max_N];

bool cmp(const string& a, const string& b) {
    if (a.size() == b.size()) return a < b;
    return a.size() < b.size();
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    sort(arr, arr + N, cmp);
    cout << arr[0];
    for (int i = 1; i < N; i++)
        if (arr[i] != arr[i - 1])
            cout << '\n' << arr[i];
    return 0;
}