#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    P frame[101];	//first : 추천 수, second : 등록 순서
    memset(frame, -1, sizeof(frame));

    // f_max : 틀 개수, f_curr : 채워진 사진틀 개수, ord : 올라간 순서
    int f_max, n, f_curr = 0, ord = 0;
    cin >> f_max >> n;
    while (n--) {
        int num; cin >> num;
        int vote = frame[num].first;

        // 해당 후보가 사진틀에 없음
        if (vote == -1) {
            // 사진틀이 다 찬 경우
            if (f_curr == f_max) {
                int MIN = INT32_MAX, target;
                loop(i, 101) {
                    int rival_vote = frame[i].first;
                    if (rival_vote == -1) continue;

                    // 추천수가 더 적거나, 추천수는 같은데 ord가 작은 경우(오래된)
                    // target에 해당 번호를 저장
                    if (rival_vote < MIN)
                        MIN = rival_vote, target = i;
                    else if (rival_vote == MIN && frame[i].second < frame[target].second)
                        target = i;
                }

                //target을 사진틀에서 뺀다.
                frame[target].first = -1, frame[target].second = -1;
                // 추천받은 후보를 올림
                // 올라갈 때 추천수는 1이며, ord는 새로운 후보가 올라갈때마다 증가
                frame[num].first = 1, frame[num].second = ++ord;
            }
            // 사진틀이 다 차지 않은 경우,
            // 누군가를 내쫓을 필요 없이 올리면 된다.
            else {
                frame[num].first = 1, frame[num].second = ++ord;
                ++f_curr;
            }
        }
        // 해당 후보가 사진틀에 있는 경우, 추천수만 1 증가
        else
            ++frame[num].first;
    }

    loop(i, 101)
        if (frame[i].first != -1)
            cout << i << ' ';
    return 0;
}