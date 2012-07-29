#!/usr/bin/ruby

puts "30 30"
arr = Array.new(30) { "?"*30 + "\n"}
arr[15][15] = "@"
puts arr
