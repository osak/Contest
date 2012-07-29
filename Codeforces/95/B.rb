#!/usr/bin/env ruby

n = gets.to_i
arr = gets.split.map(&:to_i)
dict = Hash.new(0)
arr.each do |i| 
    dict[i] += 1
end

ans = 0
ans += dict[0]*(dict[0]-1)/2 if dict[0] >= 2
(1..10).each do |i|
    ans += dict[i]*dict[-i]
end

p ans
