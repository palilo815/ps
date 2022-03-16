def main():
    ant = int(input())
    eye = int(input())
    if ant > 2 and eye < 5:
        print('TroyMartian')
    if ant < 7 and eye > 1:
        print('VladSaturnian')
    if ant < 3 and eye < 4:
        print('GraemeMercurian')


if __name__ == '__main__':
    main()
