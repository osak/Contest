#!/usr/bin/env ruby

p 64
64.times do
    cnt = (rand*3).to_i + 1
    puts "hoge #{['A', 'C', 'G'].shuffle[0,cnt].join}"
end
