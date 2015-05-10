#!/usr/bin/env ruby

def solve
  r, c, w = gets.split.map(&:to_i)
  a = c / w
  b = (c % w).zero? ? 1 : 0
  a * r + w - b
end

t = gets.to_i
t.times do |c|
  puts "Case ##{c+1}: #{solve}"
end

