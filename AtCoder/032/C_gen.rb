#!/usr/bin/env ruby

puts 100000
100000.times do |i|
  a, b = rand(1000000), rand(1000000)
  puts [a,b].sort.join(' ')
end
