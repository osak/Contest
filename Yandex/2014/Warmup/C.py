#!/usr/bin/env python

n = int(input())
radius = list()
for i in range(n):
    (a, b, c) = [int(s) for s in input().split()]
    s = (a+b+c) / 2
    area = (s*(s-a)*(s-b)*(s-c))**0.5
    radius.append(2*area / (a+b+c))

ans = 0
for target in radius:
    cnt = 0
    for rad in radius:
        if abs(target - rad) < 1e-12 or abs(1-target/rad) < 1e-12:
            cnt += 1
    ans = max(ans, cnt)
print(ans)
