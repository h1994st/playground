def main():
    n = int(raw_input())
    a = raw_input()
    a = a.split(' ')

    one = sum(x == '1' for x in a)

    ans = 0
    for i in xrange(n):
        for j in xrange(i, n):
            temp = one

            for k in xrange(i, j + 1):
                if a[k] == '1':
                    temp -= 1
                else:
                    temp += 1

            ans = max(ans, temp)

    print ans

if __name__ == '__main__':
    main()
