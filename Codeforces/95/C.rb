#!/usr/bin/env ruby

def cb(n, m)
    return 0 if n < m || m == 0
    ((n-m+1)..n).inject(&:*) / (1..m).inject(&:*)
end

n, m, t = gets.split.map(&:to_i)

ans = 0
(4..n).each do |i|
    j = t - i
    break if j == 0
    next if j > m
    ans += cb(n,i)*cb(m,j)
end
p ans
