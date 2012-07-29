#!/usr/bin/ruby

arr = gets.split.map(&:to_i)
ps = arr[0..3].sort
a,b = arr[4..5]

ans = 0
a.upto(b) { |n|
    cnt = 0
    ps.permutation { |perm|
        i = n
        perm.each { |j| i %= j }
        cnt += 1 if i == n
    }
    ans += 1 if cnt >= 7
}

p ans
