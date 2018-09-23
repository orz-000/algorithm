import numpy as np
import sys

INFTY = 99999
min = 10000
max = -1
min_i = INFTY
min_j = INFTY
max_i = INFTY
max_j = INFTY

n = input()
n = int(n)
a = [[0 for i in range(n)] for j in range(n)]

for i in range(n):
    l = list(map(int,input().split()))
    for j in range(n):
        a[i][j] = l[j]

print("\n")

for k in range(n):
    for i in range(n):
        for j in range(n):
            if(a[i][j] != INFTY and a[i][j] != 0):
                if(a[i][k] + a[k][j] < a[i][j]):
                    a[i][j] = a[i][k] + a[k][j]


for i in range(n):
    for j in range(n):
        if(a[i][j] != INFTY and a[i][j] != 0):
            if(a[i][j] < min):
                min = a[i][j]
                min_i = i
                min_j = j

            if(a[i][j] > max):
                max = a[i][j]
                max_i = i
                max_j = j


print(min,min_i,min_j)
print(max,max_i,max_j)
#for i in range(100):
#    for j in range(100):
#        print(a[i][j],end=" ")
#    print("\n")
