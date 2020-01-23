@@ - 0, 0 + 1, 40 @@
#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Count(string& ball, char key, int s, int e) {
    if (s == -1) return 987654321;
    int ret = 0;
    for (int i = s + 1;i < e;++i)
        if (ball[i] == key) ++ret;
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int len;
    string s;
    cin >> len >> s;

    // 가장 왼쪽, 오른쪽에 있는 red, blue공의 위치
    int blue_L = -1, blue_R = -1, red_L = -1, red_R = -1;
    for (int i = 0;i < len && (blue_L == -1 || red_L == -1); ++i) {
        if (s[i] == 'R' && red_L == -1) red_L = i;
        else if (s[i] == 'B' && blue_L == -1) blue_L = i;
    }
    for (int i = len - 1;i >= 0 && (blue_R == -1 || red_R == -1); --i) {
        if (s[i] == 'R' && red_R == -1) red_R = i;
        else if (s[i] == 'B' && blue_R == -1) blue_R = i;
    }

    // ** blue를 전부 왼쪽에 모이도록 만들어보자.
    // 1. red_L 왼쪽의 공은 전부 blue이며, 옮길 필요 없다. (red_L)
    // 2. red_R 오른쪽의 공은 전부 blue이며, 이것들을 전부 맨 왼쪽으로 옮겨야 한다. (len - red_R - 1)
    // 3. red_L과 red_R 사이의 공 중 blue인 애들을 전부 맨 왼쪽으로 옮겨야 한다. (Count함수)
    // 따라서 (len - red_R - 1) + (Count함수)이다.
    // ** blue를 오른쪽에 모이도록 하는건 1과 2의 경우가 바뀌어야 한다.
    // 따라서 red_L + (Count함수)이다.
    int move_B = min(red_L, len - red_R - 1) + Count(s, 'B', red_L, red_R);
    int move_R = min(blue_L, len - blue_R - 1) + Count(s, 'R', blue_L, blue_R);
    cout << min(move_B, move_R);
    return 0;
}