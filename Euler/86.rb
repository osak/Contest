#!/usr/bin/env ruby

# 直方体の3辺の長さをa, b, cとし、a ≦ b ≦ c を仮定する。
# このとき、求める最短経路は
#   sqrt((a+b)^2 + c^2)
#   sqrt((a+c)^2 + b^2)
#   sqrt((b+c)^2 + a^2)
# のどれかである。
#
# 整数解がほしいので、ピタゴラス数を列挙して、ここから辺の長さを生成することを考える。
# ピタゴラス数 x^2 + y^2 = z^2 が得られたとき、ここから導かれる直方体は
#   x = x1 + x2 とばらした (x1, x2, y)
#   y = y1 + y2 とばらした (x, y1, y2)
# のいずれか。
# 前者ではyが最大値であり、後者は必ずyを含まないため、これらの直方体は重複しない。
# これを全て数え上げ、Mの値ごとにカウントしておく。
# 探索の上限は、適当に大丈夫そうなところを設定しておく（ひどい）。

def check(a, b, c, len)
  l1 = (a+b)**2 + c**2
  l2 = (a+c)**2 + b**2
  l3 = (b+c)**2 + a**2
  [l1, l2, l3].min == len**2
end

LIMIT = 3_000_000
arr = []
list = []
seen = {}
catch(:finish) {
  (1..Float::INFINITY).each do |n|
    start = n.odd? ? 2 : 1
    (start...n).step(2) do |m|
      next if n.gcd(m) != 1
      a_base = n*n - m*m
      b_base = 2*n*m
      len_base = n*n + m*m
      a_base, b_base = b_base, a_base if b_base < a_base
      a, b, len = a_base, b_base, len_base
      throw :finish if a_base + b_base >= 100000
      while b < 10000
        (1..a/2).each do |a1|
          a2 = a - a1
          if check(a1, a2, b, len)
            tag = [a1, a2, b]
            m = tag.max
            if m <= 100
              list << tag
            end
            arr[m] ||= 0
            arr[m] += 1
          end
        end
        (1..b/2).each do |b1|
          b2 = b - b1
          if check(a, b1, b2, len)
            #puts "#{a} #{b1} #{b2}"
            tag = [a, b1, b2]
            m = tag.max
            arr[m] ||= 0
            arr[m] += 1
          end
        end
        a += a_base
        b += b_base
        len += len_base
      end
      #puts "----"
    end
  end
}

arr[0] ||= 0
(1...arr.size).each do |i|
  arr[i] ||= 0
  arr[i] += arr[i-1]
end

puts arr.size
(1..10).each do |i|
  puts "#{i}: #{arr[i]}"
end
puts "--list #{list.size}--"
puts list.map(&:inspect)
puts arr[99]
puts arr[100]
puts arr.index{|a| a >= 1_000_000}
