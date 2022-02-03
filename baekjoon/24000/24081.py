if __name__ == '__main__':
    input()
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    ans = 0
    for x in a:
        ans += x in b
    print(ans)
