#include <bits/stdc++.h>
using namespace std;

const char order[] = { 'a', 'b', 'k', 'd', 'e', 'g', 'h', 'i', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'y' };

string arr[1000];
int get_idx(char key) {
    for (int i = 0; i < 19; ++i)
        if (order[i] == key) return i << 1;
    return -1;
}
bool cmp(const string& a, const string& b) {
    const int A = a.size(), B = b.size();
    int i = 0, j = 0;
    while (1) {
        if (i >= A) return true;
        if (j >= B) return false;

        int a_val, b_val;
        if (a[i] == 'n' && i + 1 < A && a[i + 1] == 'g') {
            a_val = 21;
            ++i;
        }
        else a_val = get_idx(a[i]);

        if (b[j] == 'n' && j + 1 < B && b[j + 1] == 'g') {
            b_val = 21;
            ++j;
        }
        else b_val = get_idx(b[j]);

        if (a_val != b_val) return a_val < b_val;
        ++i, ++j;
    }
}
int main(){
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    sort(arr, arr + N, cmp);
    for (int i = 0; i < N; ++i)
        cout << arr[i] << '\n';
    return 0;
}