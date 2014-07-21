from math import sqrt

def isPrime(n):
    if n == 2 or n == 1:
        return True
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

def primes(upper):
    for i in range(1, upper + 1):
        if isPrime(i):
            print i

primes(100)

# print isPrime(4)
