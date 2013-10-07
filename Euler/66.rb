#!/usr/bin/env ruby

# ペル方程式を解く。

require 'pry'
require_relative 'pell'

max_x = 0
ans = 0
(2..1000).each do |d|
  begin
    if d == 29
      #binding.pry
    end
    x, y = each_pelleq_solutions(d).next
  rescue
    next
  end
  puts "#{d} #{x} #{y}"
  if max_x <= x
    ans = d
    max_x = x
    puts "#{ans} #{max_x}"
  end
end
puts ans
