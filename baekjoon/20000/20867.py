if __name__ == '__main__':
    m, s, g = map(int, input().split())
    a, b = map(float, input().split())
    l, r = map(int, input().split())
    print("friskus" if l / a + m / g < r / b + m / s else "latmask")
