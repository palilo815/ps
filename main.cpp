#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
	cin.tie(NULL), cout.tie(NULL);
	ios::sync_with_stdio(false);

	string A, B; cin >> A >> B;
	int pA = A.size() - 1, pB = B.size() - 1;
	int carry = 0;
	stack<int> ans;

	while (pA >= 0 && pB >= 0) {
		int tmp = carry + A[pA--] + B[pB--] - 2 * '0';
		carry = tmp / 10;
		ans.push(tmp % 10);
	}
	while (pA >= 0) {
		int tmp = carry + A[pA--] - '0';
		carry = tmp / 10;
		ans.push(tmp % 10);
	}
	while (pB >= 0) {
		int tmp = carry + B[pB--] - '0';
		carry = tmp / 10;
		ans.push(tmp % 10);
	}

	if (carry) cout << carry;
	while (!ans.empty()) {
		cout << ans.top();
		ans.pop();
	}
	return 0;
}