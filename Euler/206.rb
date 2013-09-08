#!/usr/bin/env ruby

# _が全部0のときと全部9の時の平方根を考えることで、下限と上限がわかる。
# また、求める数を(10^9a_1 + 10^8a_2 + …… + 10^1a_9 + a_10)と置いて2乗すると、
# a_10 = 0, a_9 = 3 or 7 がわかる。
# ここまで揃えば力押しで答えが出せる。
#
# 力押しでも、明らかに答えが出ない領域を飛ばすことは可能
# (平方が103...になったら112...になるまで飛ばせるなど)
# だが、そこまでやらなくても答えが出せたので実装していない。
LOW_LIM = (1020304050607080900**0.5).to_i
HIGH_LIM = (1929394959697989990**0.5).to_i

def check(n)
  return false if n % 10 != 0
  tmp = n / 100
  (1..9).reverse_each do |i|
    return false if tmp % 10 != i
    tmp /= 100
  end
  true
end

(LOW_LIM/100-1..HIGH_LIM/100+1).each do |head|
  [30, 70].each do |d2|
    i = head*100 + d2
    pow = i**2
    if check(pow)
      puts i
      puts pow
      break
    end
  end
end

