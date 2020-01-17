#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int mush[10];
int main()
{
    loop(i, 10) cin >> mush[i];
    int sum = 0;
    loop(i, 10) {
        int next = sum + mush[i];
        if (next >= 100) {
            if (next - 100 <= 100 - sum) sum = next;
            break;
        }
        sum = next;
    }
    cout << sum;
    return 0;
}