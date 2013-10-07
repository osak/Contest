#!/usr/bin/env ruby

# p1の桁数をlとすると、S = p1 + 10^l α と書ける。
# これがp2で割り切れるから
#   S ≡ 0 (mod p2)
#   p1 + 10^l α ≡ 0 (mod p2)
#   10^l α ≡ p2-p1 (mod p2)
#   (10^l % p2)(α % p2) ≡ p2-p1 (mod p2)
#   α  ≡ (p2-p1)/(10^l % p2) (mod p2)
# (10^l % p2)の逆元はフェルマーの小定理によって求めることができる。

require 'prime'

def modpow(a, x, mod)
  return 1 if x == 0
  return a % mod if x == 1
  half = modpow(a, x/2, mod)
  full = half * half
  full *= a if x.odd?
  full % mod
end

def modinv(a, mod)
  modpow(a, mod-2, mod)
end

ans = 0
prev = nil
Prime.each do |pr|
  if prev and (prev != 2) and (prev != 3)
    ord = prev.to_s.length
    m = 10**ord % pr
    inv_m = modinv(m, pr)
    rhs = (pr - prev) * inv_m % pr
    a = rhs
    n = prev + 10**ord * a
    ans += n
    if prev == 19
      puts m
      puts inv_m
      puts rhs
    end
  end
  prev = pr
  break if prev > 1_000_000
end

puts ans
