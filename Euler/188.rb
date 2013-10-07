#!/usr/bin/env ruby

# A^K % 10^8 がループする周期Mを求めたら、全ての累乗はmod Mで考えればよい。

require 'set'

MOD = 1_0000_0000
N = 1777
K = 1855
#N = 3
#K = 4

def modpow(a, x, mod)
  return 1 if x == 0
  return a if x == 1
  half = modpow(a, x/2, mod)
  val = half*half
  val *= a if x.odd?
  val % mod
end

tails = Set.new
cur = N
loop do
  break if tails.include?(cur)
  tails << cur
  cur *= N
  cur %= MOD
end
pat_mod = tails.size
puts pat_mod

cur = N
(K-2).times do
  cur = modpow(N, cur, pat_mod)
end
puts modpow(N, cur, MOD)
