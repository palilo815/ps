#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string s[3] = { "?","MS","TK" };
int judge(char a, char A)
{
	if (a == A) return 0;
	else {
		if ((a == 'R' && A == 'S') || (a == 'S' && A == 'P') || (a == 'P' && A == 'R'))
			return 1;
		else
			return 2;
	}
}
int main()
{
	cin.tie(NULL), cout.tie(NULL);
	ios::sync_with_stdio(false);

	char a, b, A, B;
	cin >> a >> b >> A >> B;
	if (a == b) {
		if (A == B)
			cout << s[judge(a, A)];
		else {
			if (judge(a, A) == 2 || judge(a, B) == 2)
				cout << s[2];
			else cout << s[0];
		}
	}
	else {
		if (A == B) {
			if (judge(a, A) == 1 || judge(b, A) == 1)
				cout << s[1];
			else cout << s[0];
		}
		else
			cout << s[0];
	}
	cout << '\n';
	return 0;
}