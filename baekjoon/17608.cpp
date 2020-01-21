#include <iostream>
using namespace std;

int height[100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0;i < N;++i)
        cin >> height[i];
    int max_h = 0, ans = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (height[i] > max_h) {
            ++ans;
            max_h = height[i];
        }
    }
    cout << ans;
    return 0;
}