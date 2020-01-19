#include <iostream>
using namespace std;

int main()
{
    int L, A, B, C, D;
    cin >> L >> A >> B >> C >> D;
    int kor = (A % C == 0) ? A / C : A / C + 1;
    int math = (B % D == 0) ? B / D : B / D + 1;
    L -= (kor > math) ? kor : math;
    cout << L;
    return 0;
}