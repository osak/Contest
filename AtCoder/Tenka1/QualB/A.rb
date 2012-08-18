#!/usr/bin/env ruby

a, b, c = gets.split.map(&:to_i)
(1..127).each do |n|
  if n % 3 == a && n % 5 == b && n % 7 == c
    puts n
  end
end

