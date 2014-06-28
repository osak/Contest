#!/usr/bin/env ruby

def fact(n)
  return 1 if n <= 0
  (1..n).inject(&:*)
end

def comb(n, k)
  num = fact(n)
  den = fact(k) * fact(n-k)
  num / den
end

data = []
(1..100).each do |n|
  (1..n).each do |k|
    data << [n, k, comb(n, k)]
  end
end

puts data.size
data.each do |n, k, res|
  puts "#{n} #{k} #{res}"
end
