#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[50][2];
int main()
{
    int N; cin >> N;
    loop(i, N) cin >> arr[i][0] >> arr[i][1];
    loop(i, N){
        int rank = 1;
        loop(j, N) {
            if (arr[j][0] > arr[i][0] && arr[j][1] > arr[i][1])
                ++rank;
        }
        cout << rank << ' ';
    }
    return 0;
}