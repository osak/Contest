#!/usr/bin/env ruby

def gcd(a, b)
  return gcd(b, a) if b > a
  if b == 0
    a
  else
    gcd(b, a % b)
  end
end

def sqrt(a)
  l = 0
  r = a
  while l+1 < r
    mid = (l + r) / 2
    if mid * mid <= a
      l = mid
    else
      r = mid
    end
  end
  l
end

t = gets.to_i
(1..t).each do |cn|
  n, l = gets.split.map(&:to_i)
  ls = gets.split.map(&:to_i)
  plain_text = []
  (0...ls.size-1).each do |i|
    a = ls[i]
    b = ls[i+1]
    if a == b
      plain_text << -1
    else
      gcd_val = gcd(a, b)
      plain_text << gcd_val
    end
  end

  plain_text.unshift(-1)
  plain_text << -1

  (1...plain_text.size).each do |i|
    if plain_text[i] == -1 && plain_text[i-1] != -1
      plain_text[i] = ls[i-1] / plain_text[i-1]
    end
  end
  (0...plain_text.size-1).reverse_each do |i|
    if plain_text[i] == -1 && plain_text[i+1] != -1
      plain_text[i] = ls[i] / plain_text[i+1]
    end
  end

  dict = {}
  plain_text.sort.uniq.each_with_index do |pr, i|
    dict[pr] = ('A'.ord + i).chr
  end

  text = plain_text.map{|num| dict[num]}.join
  puts "Case ##{cn}: #{text}"
end

