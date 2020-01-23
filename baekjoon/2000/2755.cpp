#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int arr[] = { 400,300,200,100,0,0 };
    int N; cin >> N;
    int grade = 0, total = 0;
    loop(i, N) {
        string name, Grade;
        int x;
        cin >> name >> x >> Grade;
        total += x;
        int tmp = arr[Grade[0] - 'A'];
        if (Grade.size() > 1) {
            if (Grade[1] == '+') tmp += 30;
            else if (Grade[1] == '-') tmp -= 30;
        }
        grade += tmp * x;
    }
    cout << grade / total / 100 << '.';
    cout << (grade / total / 10) % 10;
    cout << (grade / total) % 10 + ((grade % total) * 2 >= total) ? 1 : 0;
    return 0;
}