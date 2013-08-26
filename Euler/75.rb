#!/usr/bin/env ruby

# ピタゴラス数を列挙する問題。
# 原始ピタゴラス数(a, b, cが互いに素なピタゴラス数)は、以下の式で網羅的に生成できる。
#   a = n^2 - m^2
#   b = 2nm
#   c = n^2 + m^2
#   where
#     gcd(n, m) = 1
#     n - m ≡ 1 (mod 2)

cnt = Array.new(1500001, 0)
(1..Float::INFINITY).each do |n|
  start = n.odd? ? 2 : 1
  if 2*n + n*n >= cnt.size
    break
  end
  (start...n).step(2) do |m|
    next if n.gcd(m) != 1
    a = n*n - m*m
    b = 2*n*m
    c = n*n + m*m
    base = a+b+c
    len = base
    while len < cnt.size
      cnt[len] += 1
      len += base
    end
  end
end

(1..120).each do |i|
  if cnt[i] > 0
    puts "#{i} #{cnt[i]}"
  end
end

puts cnt.count(1)
