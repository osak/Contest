#!/usr/bin/env ruby

require 'matrix'

MOD = 10**9 + 7

class Matrix
  def %(val)
    self.map{|v| v % val}
  end
end

def modpow(a, x)
  return 1 if x == 0
  return a if x == 1
  half = modpow(a, x/2)
  rem = x.odd? ? a : 1
  half * half * rem % MOD
end

bases = []
mat = Matrix[[1, 1, 1], [1, 0, 0], [0, 1, 0]]
50.times do
  bases << mat.dup
  mat *= mat
  mat %= MOD
  puts mat
end
puts modpow(2, 10**15)

t = gets.to_i
t.times do
  n = gets.to_i
  mat = Matrix.I(3)
  pow_n = n-1
  50.times do |bit|
    if pow_n.odd?
      mat *= bases[bit]
      mat %= MOD
    end
    pow_n >>= 1
  end
  vec = mat * Matrix[[1], [1], [0]]
  sum = vec.to_a.flatten.inject(&:+)
  all_pat = modpow(2, n)
  puts (all_pat - sum + MOD) % MOD
end
