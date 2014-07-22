def main():
    a = raw_input()
    a = a.split(' ')
    n = int(a[0])
    m = int(a[1])

    a = raw_input()
    a = a.split(' ')

    b = range(n)

    while len(b) != 0:
        if int(a[b[0]]) <= m:
            if len(b) == 1:
                print b[0] + 1
            del b[0]
        else:
            a[b[0]] = int(a[b[0]]) - m
            b = b[1:] + b[0:1]

if __name__ == '__main__':
    main()