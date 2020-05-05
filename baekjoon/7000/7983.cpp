#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000000;

p arr[max_N];

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N; cin >> N;
	loop(i, N) cin >> arr[i].second >> arr[i].first;
	sort(arr, arr + N, greater<p>());

	int start = INT_MAX;
	loop(i, N) {
		auto [t, d] = arr[i];
		if (t < start) start = t;
		start -= d;
	}
	cout << start;
	return 0;
}