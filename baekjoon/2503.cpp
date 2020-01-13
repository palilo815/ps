#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
bool DiffDigits(int num)
{
    int a = num % 10;
    if (a == 0) return false;
    num /= 10;
    int b = num % 10;
    if (b == 0) return false;
    num /= 10;
    int c = num;
    if (c == 0) return false;

    return a != b && b != c && c != a;
}
int Strike(int a, int b)
{
    int count = 0;
    if (a % 10 == b % 10) count++;
    a /= 10, b /= 10;
    if (a % 10 == b % 10) count++;
    a /= 10, b /= 10;
    if (a == b) count++;
    return count;
}
int Ball(int a, int b)
{
    int count = 0, b_1, b_2, b_3;
    b_1 = b % 10;
    b /= 10;
    b_2 = b % 10;
    b /= 10;
    b_3 = b;
    if (a % 10 == b_2 || a % 10 == b_3) count++;
    a /= 10;
    if (a % 10 == b_1 || a % 10 == b_3) count++;
    a /= 10;
    if (a == b_1 || a == b_2) count++;
    return count;
}
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    queue<int> q;
    for (int i = 100; i < 1000; i++)
        if (DiffDigits(i)) q.push(i);

    int n, num1, num2, S, B, size;
    cin >> n;
    while (n-- > 0) {
        cin >> num1 >> S >> B;
        size = q.size();
        while (size-- > 0) {
            num2 = q.front();
            q.pop();
            if (S == Strike(num1, num2) && B == Ball(num1, num2))
                q.push(num2);
        }
    }
    cout << q.size();
    return 0;
}