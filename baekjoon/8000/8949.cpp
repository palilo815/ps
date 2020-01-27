#include<bits/stdc++.h>
using namespace std;

int main()
{
    int A, B; cin >> A >> B;
    stack<int> Ans;
    while (A || B) {
        Ans.push(A % 10 + B % 10);
        A /= 10, B /= 10;
    }
    while (!Ans.empty()) {
        cout << Ans.top();
        Ans.pop();
    }
    return 0;
}