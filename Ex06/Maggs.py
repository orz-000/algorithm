import numpy as np
import sys

INFTY = 99999
sum = 0
maxi = -1

n = input()
n = int(n)
a = [[0 for i in range(n)] for j in range(n)]
b = [[0 for i in range(n)] for j in range(n)]

for i in range(n):
    l = list(map(int,input().split()))
    for j in range(n):
        a[i][j] = l[j]

for i in range(n):
    for j in range(n):
        b[i][j] = a[i][j]


for k in range(n):
    for i in range(n):
        for j in range(n):
            a[i][j] = min( a[i][j], max(a[i][k],a[k][j]) )


#                if(a[i][k] < a[k][j]):
#                    max = a[k][j]
#                else:
#                    max = a[i][k]
#                if(a[i][j] > max):
#                    a[i][j] = max

print(b)
for i in range(n):
    for j in range(n):
        if(a[i][j] != b[i][j] and a[i][j] != INFTY):
            sum += a[i][j]

print(sum)
#for i in range(100):
#    for j in range(100):
#        print(a[i][j],end=" ")
#    print("\n")
