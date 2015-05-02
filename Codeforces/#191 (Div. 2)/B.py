def main():
    n = int(raw_input())

    # Solution 1
    # 
    # ans = 10000000 - n + 1
    # for i in xrange(n):
    #     print '%d ' % ans,
    #     ans += 1

    # Solution 2
    # 
    # Too slow
    # 
    MAX = 10000000
    primes = range(MAX + 1)
    primes[1] = 0
    for i in xrange(2, MAX + 1, 2):
        for j in xrange(i + i, MAX + 1, i):
            primes[j] = 0

    i = 2
    while n > 0:
        if primes[i] != 0:
            print '%d ' % i,
            n -= 1
        i += 1

if __name__ == '__main__':
    main()
