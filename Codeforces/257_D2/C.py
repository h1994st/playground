def main():
    info = raw_input().split(' ')
    n = int(info[0])
    m = int(info[1])
    k = int(info[2])

    if m + n - 2 < k:
        print -1
    else:
        pass

if __name__ == '__main__':
    main()
