#!/usr/bin/env ruby

puts "1000 1000"
1000.times do |i|
  puts Array.new(1000){rand(100000)}.join(' ')
end

