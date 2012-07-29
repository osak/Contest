#!/usr/bin/env ruby

n = gets.to_i
cs = gets.chomp.each_char.to_a.map(&:to_i)

cnt = Array.new(4){|i| cs.count(i+1)}
puts "#{cnt.max} #{cnt.min}"
