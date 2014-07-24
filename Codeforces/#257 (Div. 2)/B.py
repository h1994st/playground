info = raw_input().split(' ')
x = int(info[0])
y = int(info[1])

def main():
    n = int(raw_input())
    f = [x, y, y - x, -x, -y, x - y]
    print f[n % 6 - 1] % int(1e9 + 7)

if __name__ == '__main__':
    main()
