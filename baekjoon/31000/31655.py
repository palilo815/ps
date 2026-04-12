def main():
    s = input()
    a, b, _ = map(int, s.split("/"))
    ans = "EU" if a > 12 else "US" if b > 12 else "either"
    print(ans)


if __name__ == "__main__":
    main()
