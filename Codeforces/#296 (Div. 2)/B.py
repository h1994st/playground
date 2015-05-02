def main():
    n = int(raw_input())
    str1, str2 = raw_input(), raw_input()

    hd = 0
    temp = []
    for i in xrange(n):
        if str1[i] != str2[i]:
            hd += 1
            temp.append(i)

    if hd < 2:
        print hd
        print '-1 -1'
        return

    ans, a, b = hd, -1, -1
    for i in xrange(hd):
        for j in xrange(i + 1, hd):
            i1, i2 = temp[i], temp[j]
            if str1[i1] == str2[i2] and str1[i2] == str2[i1]:
                print hd - 2
                print '%d %d' % (i1 + 1, i2 + 1)
                return

            if str1[i1] == str2[i2] or str1[i2] == str2[i1]:
                ans, a, b = hd - 1, i1 + 1, i2 + 1

    print ans
    print '%d %d' % (a, b)

if __name__ == '__main__':
    main()
