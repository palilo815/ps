#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int max_N = 3000;
const int max_num = 1000000;

int arr[max_N];
bool num[max_num + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
        num[arr[i]] = true;
    }

    ll ans = 0;
    for (int i = 0; i < N - 1; ++i)
        for (int j = i + 1; j < N; ++j) {
            int gap = arr[j] - arr[i];
            int k = arr[j];
            while (k + gap <= max_num && num[k + gap])
                k += gap;

            if (k == arr[j]) continue;
            ans = max(ans, ((ll)arr[i] + k) * ((k - arr[i]) / gap + 1) / 2);
        }
    cout << ans;
    return 0;
}