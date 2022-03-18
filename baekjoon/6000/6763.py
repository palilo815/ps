if __name__ == '__main__':
    v = -int(input()) + int(input())
    if v < 1:
        print("Congratulations, you are within the speed limit!")
    else:
        if v < 21:
            fine = 100
        elif v < 31:
            fine = 270
        else:
            fine = 500
        print("You are speeding and your fine is $%d." % fine)
