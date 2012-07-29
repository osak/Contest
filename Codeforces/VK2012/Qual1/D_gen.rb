#!/usr/bin/env ruby

puts "20000"
puts Array.new(20000) {(rand*2000 - 1000).to_i}.join(' ')
