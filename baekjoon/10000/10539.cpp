#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[100];
int main()
{
    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    int psum = 0;
    loop(i, N) {
        int a = arr[i] * (i + 1) - psum;
        psum += a;
        cout << a << ' ';
    }
    return 0;
}