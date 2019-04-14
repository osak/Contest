#!/usr/bin/env ruby

t = gets.to_i
(1..t).each do |cn|
  n = gets.to_i
  s = gets.chomp
  puts "Case ##{cn}: #{s.tr('SE', 'ES')}"
end

