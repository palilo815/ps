#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n;
	cin >> n;
	cin.ignore();
	int count = 0;
	while (n-- > 0) {
		bool flag = true;
		string str;
		getline(cin, str);
		for (int i = 1; i < str.length(); i++) {
			if (str[i] != str[i - 1]) {
				for (int j = 0; j < i; j++) {
					if (str[j] == str[i]) {
						flag = false;
						break;
					}
				}
			}
		}
		if (flag)
			count++;
	}
	cout << count;
	return 0;
}