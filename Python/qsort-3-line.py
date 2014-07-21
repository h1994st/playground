import random

def qsort(L):  
	if len(L) <= 1: return L  
	return qsort([lt for lt in L[1:] if lt < L[0]]) + L[0:1] + qsort([ge for ge in L[1:] if ge >= L[0]])

def qsort2(L):  
    if not L:
        return L
    pivot = L[0]

    def lt(x):
        return x<pivot

    def ge(x):
        return x>=pivot

    return qsort2(filter(lt, L[1:]))+[pivot]+qsort2(filter(ge, L[1:]))

def qsort3(L):  
    if not L:
        return L  
    pivot = random.choice(L)

    def lt(x):
        return x<pivot

    def gt(x):
        return x>pivot

    return qsort3(filter(lt, L))+[pivot]*L.count(pivot)+qsort3(filter(gt, L))

list = range(1000)
random.shuffle(list)

print list
print qsort(list)
print list
print qsort2(list)
print list
print qsort3(list)
