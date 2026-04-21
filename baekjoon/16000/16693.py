import math


def main():
    a, p1 = map(int, input().split())
    r, p2 = map(int, input().split())
    slice, whole = a / p1, math.pi * r**2 / p2
    print(f"{'Slice of' if slice > whole else 'Whole'} pizza")


if __name__ == "__main__":
    main()
