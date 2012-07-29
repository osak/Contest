#!/usr/bin/ruby

p 1
p 1000
arr = (1..999).to_a
arr << arr.inject(&:^)
puts arr.join(' ')
