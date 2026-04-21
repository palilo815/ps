def main():
    s = input()
    ans = (
        "digital humanities"
        if any(key in s for key in ["social", "history", "language", "literacy"])
        else "public bigdata"
    )
    print(ans)


if __name__ == "__main__":
    main()
