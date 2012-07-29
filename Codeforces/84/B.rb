#!/usr/bin/ruby

n = gets.to_i
str = 'abcd' * (n / 4)
str << 'abcd'[0...(n%4)]
puts str
