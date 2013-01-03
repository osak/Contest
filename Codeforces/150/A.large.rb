#!/usr/bin/ruby

puts "10000"
puts Array.new(10000){(rand*100000).to_i}.join(' ')
