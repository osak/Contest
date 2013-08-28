#!/usr/bin/env ruby

# 多倍長整数の力で1桁ずつ決めていく。

def long_sqrt(n)
  base = (n**0.5).to_i
  big_n = n
  100.times do
    base *= 10
    big_n *= 100
    (0..9).reverse_each do |digit|
      tmp = base + digit
      if tmp * tmp <= big_n
        base += digit
        break
      end
    end
  end
  base
end

puts (1..100).to_a.select{|i| ((i**0.5).to_i)**2 != i}.map{|i| long_sqrt(i).to_s.each_char.to_a[0...100].map(&:to_i).inject(&:+)}.inject(&:+)
