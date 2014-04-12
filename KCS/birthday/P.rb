#!/usr/bin/env ruby

x = 0
n, m = gets.split.map(&:to_i)
i = 0
loop do
  x += i
  x %= 65536
  break if i == n
  i += m
  i %= 65536
  break if i == 0
end
puts x
