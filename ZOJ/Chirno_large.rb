#!/usr/bin/env ruby

n, r, l = ARGV.map(&:to_i)
puts "#{n} #{r} #{l}"
(n-1).times do
    puts Array.new(2) { (rand*1000000).to_i }.join(' ')
end
puts "1000000000 1000000000"
puts Array.new(2) { (rand*1000000).to_i }.join(' ')
