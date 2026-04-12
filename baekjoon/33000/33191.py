def main():
    budget = int(input())
    for item in ["Watermelon", "Pomegranates", "Nuts"]:
        if int(input()) <= budget:
            print(item)
            return
    print("Nothing")


if __name__ == "__main__":
    main()
