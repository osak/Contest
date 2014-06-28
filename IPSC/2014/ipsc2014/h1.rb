#!/usr/bin/env ruby

cap = 16
threshold = 12

ord = 1
25000.times do |i|
  puts i + (i<<32)
  ord += 1
=begin
  if i >= threshold
    cap *= 2
    threshold *= 2
    ord = 1
  end
=end
end
