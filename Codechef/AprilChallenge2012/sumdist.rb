#!/usr/bin/ruby

h = Hash.new(0)
(1..gets.to_i).each do |i|
  sum = i.to_s.each_char.to_a.map(&:to_i).inject(&:+)
  h[sum] += 1
end

h.each_pair do |key, val|
  printf("%6d: %6d\n", key, val)
end
