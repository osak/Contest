#!/usr/bin/ruby

NUM = 2500
arr = []
NUM.times do |i|
    arr << "."*NUM
end
arr[NUM/2][NUM/2] = 'S'
arr[0][0] = 'T'
puts "#{NUM} #{NUM}"
puts arr.join("\n")
