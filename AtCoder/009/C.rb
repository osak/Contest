#!/usr/bin/ruby

MOD = 1777777777

def modpow(a, x)
  return 1 if x == 0
  return a if x == 1
  half = modpow(a, x/2)
  rem = x.odd? ? a : 1
  ((half * half) % MOD) * rem % MOD
end

def comb(n, k)
  res = 1
  ((n-k+1)..n).each do |i|
    res *= i
    res %= MOD
  end
  (1..k).each do |i|
    inv = modpow(i, MOD-2)
    res *= inv
    res %= MOD
  end
  res
end

n, k = gets.split.map(&:to_i)
# dp[k] = [k個全部バラバラ, k-1個バラバラ]
dp = Array.new(k+1){Array.new(2)}
dp[1] = [0, 1]
(2..k).each do |i|
  dp[i][0] = (dp[i-1][0]*(i-1) + dp[i-1][1]) % MOD
  dp[i][1] = dp[i-1][0]*i % MOD
end

puts (dp[k][0] * comb(n, k)) % MOD
