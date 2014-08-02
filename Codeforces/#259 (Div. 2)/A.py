def main():
    n = int(raw_input())

    for x in range(n):
        a = min(x, n - x - 1) * 2 + 1
        b = (n - a) / 2
        print '*' * b + 'D' * a + '*' * b

if __name__ == '__main__':
    main()