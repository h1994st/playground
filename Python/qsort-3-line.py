import random

def qsort(L):  
	if len(L) <= 1: return L  
	return qsort([lt for lt in L[1:] if lt < L[0]]) + L[0:1] + qsort([ge for ge in L[1:] if ge >= L[0]])

list = []
for i in range(100):
	list.append(random.randint(0, 10000))

print list
print qsort(list)
