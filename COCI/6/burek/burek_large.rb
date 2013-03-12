#!/usr/bin/ruby

puts "100000"
100000.times do
  puts Array.new(6){(rand*100000).to_i}.join(' ')
end
puts "100000"
100000.times do
  axis = ["x", "y"].sample
  puts "#{axis} = #{(rand*100000).to_i}"
end
