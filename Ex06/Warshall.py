import numpy as np
import sys

n = input()
n = int(n)
a = [[0 for i in range(n)] for j in range(n)]
d = []

for i in range(n):
    l = list(map(int,input().split()))
    for j in range(n):
        a[i][j] = l[j]

print("\n")

for k in range(n):
    for i in range(n):
        for j in range(n):
            a[i][j] = a[i][j] or (a[i][k] and a[k][j])

for i in range(n):
    flag = True
    for j in range(n):
        if(a[j][i] == 1):
            flag = False
            break
    if(flag == True):
        print('a')
        d.append(i)

print(d)
#for i in range(100):
#    for j in range(100):
#        print(a[i][j],end=" ")
#    print("\n")
