# 
# Time limit exceeded on test 9
# 

mod = 1000000007

def main():
    a = str(int(raw_input()))
    k = int(raw_input())

    ans = 0
    for i in xrange(len(a)):
        if a[i] == '0' or a[i] == '5':
            n = k
            base = 0
            while n > 0:
                ans = (ans + pow(2, base + i, 1000000007)) % 1000000007

                base += len(a)
                n -= 1

    print ans

if __name__ == '__main__':
    main()
