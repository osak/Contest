#!/usr/bin/env python

(n, k) = [int(s) for s in input().split()]
fact = 1
total = 1
for i in range(1, n+1):
    fact *= i
    total += fact ** k
while total % 10 == 0:
    total //= 10
print(total % 10)
