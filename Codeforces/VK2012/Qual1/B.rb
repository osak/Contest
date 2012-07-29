#!/usr/bin/env ruby

n = gets.to_i
arr = gets.split.map(&:to_i)
h = Array.new(5, 0)
arr.each do |i|
  h[i] += 1
end

ans = h[4]

# Make as many 4s as possible
threes = [h[1], h[3]].min
ans += threes
h[1] -= threes
h[3] -= threes
if h[3] > 0
  ans += h[3]
  h[3] = 0
end

twos = h[2] / 2
ans += twos
h[2] -= twos*2
if h[2] > 0
  ones = [2, h[1]].min
  ans += 1
  h[2] = 0
  h[1] -= ones
end

if h[1] > 0
  ans += (h[1]+3) / 4
end

p ans
