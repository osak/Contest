#!/usr/bin/env ruby

# mod 10**10で計算するだけ。

n = 28433
7830457.times do
  n *= 2
  n %= 10**10
end
n += 1
puts n
