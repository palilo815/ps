#include<iostream>
#include<algorithm>
using namespace std;

bool Yujun(string num, int loc)
{
    int mul_1 = 1, mul_2 = 1, i;
    for (i = 0; i < loc;i++)
        mul_1 *= num[i] - '0';
    for (i; i < num.length(); i++)
        mul_2 *= num[i] - '0';
    return mul_1 == mul_2;
}

int main()
{
    string num;
    cin >> num;

    bool flag = false;
    for (int i = 1; i < num.length(); i++) {
        if (Yujun(num, i)) {
            flag = true;
            break;
        }
    }
    if (flag) cout << "YES";
    else cout << "NO";
    return 0;
}