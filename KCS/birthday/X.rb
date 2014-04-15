#!/usr/bin/env ruby

arr = %w(1 64 77 40 53 16 29 92 5 68 81 44 57 20 33 96 9 72 85 48).map(&:to_i)
n = gets.to_i
res = []
arr.each_with_index do |v, i|
  if i.even?
    res << (v+n-1) % 100
  else
    res << (v+51*(n-1)) % 100
  end
end
puts res.join(' ')
