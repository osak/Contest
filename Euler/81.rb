#!/usr/bin/env ruby

# 典型的DP。

field = File.read("matrix.txt").lines.map{|l| l.split(/,/).map(&:to_i)}
(0...80).each do |r|
  (0...80).each do |c|
    next if r == 0 and c == 0
    min = 1e10
    min = [min, field[r-1][c]].min if r-1 >= 0
    min = [min, field[r][c-1]].min if c-1 >= 0
    field[r][c] = min + field[r][c]
  end
end

puts field[-1][-1]
