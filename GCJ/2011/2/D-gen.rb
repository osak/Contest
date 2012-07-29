#!/usr/bin/ruby

puts "1"
puts "36 630"
arr = []
36.times do |i|
    i.times do |j|
        arr << "#{i},#{j}" unless i == 1 && j != 35
    end
end

#(2..34).each do |i|
#    arr << "#{i},#{i+1}"
#end
#arr << "0,2"
#arr << "35,1"

puts arr.join(" ")
