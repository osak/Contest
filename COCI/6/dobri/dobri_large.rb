#!/usr/bin/ruby

puts "5000"
puts Array.new(5000){(rand*200000).to_i-100000}.join(' ')
