import sys
sys.setrecursionlimit(10**6)
input = sys.stdin.readline

def stat(team):
    ret = 0
    for a in team:
        for b in team:
            ret += mat[a][b]
    return ret


def solve(idx):
    if idx == N:
        global ans
        ans = min(ans, abs(stat(team1) - stat(team2)))
        return

    team1.append(idx)
    solve(idx + 1)
    team1.pop()
    team2.append(idx)
    solve(idx + 1)
    team2.pop()


N = int(input())
mat = []
for i in range(N):
    mat.append(list(map(int, input().split())))

ans = sys.maxsize
team1, team2 = [], []

solve(0)
print(ans)
