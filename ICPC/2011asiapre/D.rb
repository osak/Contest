#!/usr/bin/env ruby

a = 0
ARGV[0].to_i.times do |i|
    a += (i+1)*(9*(10**i))
end

puts a
puts a.to_s.size
