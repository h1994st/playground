def main():
    n = int(raw_input())
    origin, target = raw_input(), raw_input()

    ans = 0
    for i in xrange(n):
        offset = abs(int(origin[i]) - int(target[i]))
        if offset > 10 - offset:
            offset = 10 - offset
        ans = ans + offset

    print ans

if __name__ == '__main__':
    main()
