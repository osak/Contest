#!/usr/bin/env ruby

MOD = 1000000007
def modpow(a, x)
  return 1 if x == 0
  return a if x == 1
  half = modpow(a, x/2) % MOD
  rem = x.odd? ? a : 1
  half * half * rem % MOD
end

t = gets.to_i
t.times do
  n = gets.to_i
  lim = n / 2
  sum = (modpow(2, lim+1) - 1) * 2 - 1
  sum = (sum - modpow(2, lim) + MOD) % MOD if n.even?
  sum += 1
  puts sum % MOD
end
