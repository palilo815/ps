#include<iostream>
using namespace std;

typedef struct nara {
    int name;
    int gold;
    int silver;
    int bronze;
} Nara;

int main()
{
    int N, K, G, S, B;
    cin >> N >> K;
    Nara* arr = new Nara[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i].name >> arr[i].gold >> arr[i].silver >> arr[i].bronze;
        if (arr[i].name == K)
            G = arr[i].gold, S = arr[i].silver, B = arr[i].bronze;
    }
    int count = 1;
    for (int i = 0; i < N; i++) {
        if (arr[i].gold > G) ++count;
        else if (arr[i].gold == G) {
            if (arr[i].silver > S) ++count;
            else if (arr[i].silver == S)
                if (arr[i].bronze > B) ++count;
        }
    }
    cout << count;
    return 0;
}