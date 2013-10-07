#!/usr/bin/env ruby

# 素因数の個数を小さい方から決めていく探索をする。

require 'prime'

PRIMES = Prime.each(100).to_a
LIMIT = 10**9

cnt = 1
stk = [[1,0]]
while stk.size > 0
  cur = stk.pop
  (cur[1]...PRIMES.size).each do |idx|
    nv = cur[0] * PRIMES[idx]
    if nv <= LIMIT
      cnt += 1
      stk << [nv, idx]
    end
  end
end
puts cnt
