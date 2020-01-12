#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define eps 1e-9	// 유효 오차

int main()
{
	cin.tie(NULL), cout.tie(NULL);
	ios::sync_with_stdio(false);

	int t;
	cin >> t;
	double x1, x2, y1, y2, r1, r2;
	while (t-- > 0) {
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		// case 1 : 완전 일치
		if (x1 == x2 && y1 == y2 && r1 == r2) {
			cout << "-1" << '\n';
			continue;
		}

		// d : (x1,y1) ~ (d2,y2) distance
		// small_r, large_r
		double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		double s_r = min(r1, r2), l_r = max(r1, r2);
		int ans;

		// case 2 : 한 원이 다른 원의 내부
		if (d + s_r - l_r < eps) {
			// 접한다
			if (d + s_r - l_r > -eps)
				ans = 1;
			// 접하지 않으면 만나지 않음
			else
				ans = 0;
		}
		// case 3 : 다른 원 밖
		else {
			// 접한다
			if (fabs(s_r + l_r - d) < eps)
				ans = 1;
			// 만나지 않음
			else if (d - s_r - l_r > eps)
				ans = 0;
			// 그 이외 : 두 점에서 교차
			else
				ans = 2;
		}
		cout << ans << '\n';
	}
	return 0;
}