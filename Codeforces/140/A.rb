#!/usr/bin/env ruby

def modpow(a, x, mod)
  return 1 if x == 0
  return a if x == 1
  half = modpow(a, x/2, mod)
  rem = x.odd? ? a : 1
  half * half * rem % mod
end

n, m = gets.split.map(&:to_i)
puts (modpow(3, n, m) + m - 1) % m
