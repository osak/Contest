#!/usr/bin/env ruby

p 1000
1000.times do
    b = (rand*1000).to_i
    w = (rand*1000).to_i
    h = (rand*1000).to_i
    s = -(rand*1000).to_i

    puts "#{b} #{w} #{h} #{s}"
end

puts "500 500 500"

